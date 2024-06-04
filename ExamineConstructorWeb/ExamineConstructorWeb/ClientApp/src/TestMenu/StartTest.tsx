import React, {useEffect, useState} from 'react';
import "./TestMenu.scss";
import {useNavigate, useParams} from "react-router-dom";


interface IStartTestProps {
    user:IUserData,
    Tests:ITest[],
    SetRaiting: (raiting:IRaiting)=>void
}
export const StartTest:React.FC<IStartTestProps> = (
    {
        user,
        Tests,
        SetRaiting
    }
        )=>{
    let {TestId} = useParams();
    let [Test, setTest] = useState({
        id: 0,
        name: "",
        questions_St: [],
        difficulty: 0,
        authorid: 0,
        description: ""
    } as ITest)
    let [TestPass, setTestPass] = useState({} as ITestPass)
    let history = useNavigate();
    
    
    
    useEffect(() => {
        let test = Tests.find(t=> t.id == Number(TestId));
        if(test == undefined) {
            alert("ошибка")
            history("/")
            return
        }
        setTest(test);
        setTestPass({
            TestId: test.id,
            UserId: user.id,
            questions_St: new Array<IQue_pass>(test.questions_St.length),
            Difficulty: test.difficulty
        } as ITestPass)
    }, [Tests]);
    
    
    let handlerFinishTest =async ()=>{
        await fetch("https://localhost:7148/api/Tests/check",{
            method:"POST",
            headers:{
                "Content-Type":"application/json"
            },
            body:JSON.stringify(TestPass)
        }).then(res=>res.json())
            .then(data=>{
                if(data){
                    let raiting = {
                        id: data.id,
                        userId: data.userId,
                        score: data.score,
                        testId: data.testId,
                    } as IRaiting
                    if(Tests.find(t=>t.id == raiting.testId)){
                        setTestPass({} as ITestPass)
                        setTest({} as ITest)
                        SetRaiting(raiting);
                        history(`/result/${raiting.id}`)
                    }
                }
            })
    }
    
    
    return (
        <div className={"Start-test-page"}>
            <div className="start-test-desc">
                <h1>Название: {Test.name}</h1>
                <h2>Сложность: {Test.difficulty}</h2>
                <h2>Описание : {Test.description}</h2>
            </div>
            <div className="st-test-quiz">
                {Test.questions_St && Test.questions_St.map((que,index)=>{
                    return (
                        <div 
                            className={"test-Question-menu"}
                            key={index}
                        >
                            <h2>Вопрос {index+1}. {que.question}</h2>
                            <h2>Сложность: {que.difficulty}</h2>
                            <textarea name="ansver" id="que-answer" 
                                onChange={(e)=>{
                                    let testPass = TestPass;
                                    testPass.questions_St[index] = {
                                        Id: que.id,
                                        Answer: e.target.value,
                                        Difficulty: que.difficulty
                                    }
                                    setTestPass(testPass);
                                }}
                            ></textarea>
                        </div>
                    )
                })}
            </div>
            <div className="finish-test-controll">
                <button
                    className={"finish-test-button"}
                    onClick={handlerFinishTest}
                >
                    Завершить тест
                </button>
            </div>
        </div>    
    )
}
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
interface IQue_pass {
    Id: number;
    Answer: string;
    "Difficulty":number
}

interface ITestPass {
    TestId: number;
    UserId: number;
    questions_St: Array<IQue_pass>;
    Difficulty: number;
}




interface IRaiting {
    "id": number,
    "userId": number,
    "user": null,
    "score": number,
    "testId": number,
    "test": null
}