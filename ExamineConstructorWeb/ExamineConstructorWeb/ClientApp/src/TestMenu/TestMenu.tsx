import React from 'react';
import './TestMenu.scss';
import {useNavigate, useParams} from "react-router-dom";
interface ITestMenuProps {
    user:IUserData,
    Tests:ITest[]
}
export const TestMenu:React.FC<ITestMenuProps> = (
    {
        user,
        Tests
    }
) => {
    let {TestId} = useParams();
    let test = Tests.find(test => test.id === Number(TestId));
    let [Raiting,setRaiting] = React.useState([] as Array<IRaiting>);
    let [isLoad,setIsLoad] = React.useState(false);
    let history = useNavigate();
    
    React.useEffect(()=>{
        setIsLoad(true);
        getData();
    },[TestId])
    
        
    let getData = async () => {
        await fetch(`https://localhost:7148/api/Raiting/${TestId}`,{
            method: "GET",
            headers: {
                'Content-Type': 'application/json',
                "Authorization": "Bearer " + localStorage.getItem("token")
            }
        }).then(response => response.json())
            .then((data:IRaiting[]) => {
                setIsLoad(false);
                if(data.length>0){
                    setRaiting(data.sort((a,b) => b.score - a.score));
                }   
            })
    }
    let handleStartTest = (TestId:number|undefined) => {
        if(TestId === undefined) alert("ошибка")
        history(`/pass/${TestId}`)
    }
    
    let handleExport = () =>{
let element = document.createElement('a');
        element.setAttribute('href', 'data:text/plain;charset=utf-8,' + encodeURIComponent(JSON.stringify(test)));
        element.setAttribute('download', test?.name + ".json");
      
        element.style.display = 'none';
        document.body.appendChild(element);
      
        element.click();
      
        document.body.removeChild(element);        
    }
    
    return (
        <div className={"TestMenu"}>
            <div className="TestInfo">
                <h2>Название: {test?.name}</h2>
                <h2>Описание: {test?.description}</h2>
                <h2>Количество вопросов: {test?.questions_St.length}</h2>
                <h2>Сложность: {test?.difficulty}</h2>
                <div className="test-controll">
                    <button
                        className={"start-test"}
                        onClick={() => handleStartTest(test?.id)}
                    >Пройти Тест</button>
                    <button
                        className={"edit-test"}
                        onClick={() => history(`/update/${test?.id}`)}
                    >Редактировать</button>
                    <button
                        className={"download"}
                        onClick={handleExport}
                    >Скачать тест</button>
                    <button
                        className={"test-back"}
                        onClick={() => history("/")}
                    >Назад</button>
                </div>
                
            </div>
            <div className="Raiting">
                {isLoad ? "Loading..." : null}
                <h1>Рейтинг</h1>
                <div  className="RaitingItem">
                    <h2 className="RaitingItemName">
                        Номер: 
                    </h2>
                    <h2 className="RaitingItemScore">
                        балл: 
                    </h2>
                </div>
                {
                    Raiting.map((rait: IRaiting, index: number) => {
                        return (
                            <div key={index} className="RaitingItem">
                                <h2 className="RaitingItemName">
                                    {rait.userId}
                                </h2>
                                <h2 className="RaitingItemScore">
                                    {rait.score}
                                </h2>
                            </div>
                            
                        )
                    })
                }
                { Raiting.length === 0 && <h2>Нет прохождений</h2>
                    
                }
                
                
            </div>
        </div>
    );
};


interface IUserData {
    id: number;
    name: string;
    surname: string;
    email: string;
    age: number;
    login: string;
    password: string;
    ruleLevel: number;
}

interface ITest {
    id: number;
    name: string;
    questions_St: Array<IQuestion_st>;
    difficulty: number;
    authorid: number;
    description: string;
}

interface IQuestion_st {
    id: number;
    question: string;
    difficulty: number;
}

interface IRaiting {
    "id": number,
    "userId": number,
    "user": null,
    "score": number,
    "testId": number,
    "test": null
}