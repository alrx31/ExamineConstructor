import React, {useEffect, useState} from 'react';
import "./TestMenu.scss";
import {useNavigate, useParams} from "react-router-dom";


interface IStartTestProps {
    user:IUserData,
    Tests:ITest[]
}
export const StartTest:React.FC<IStartTestProps> = (
    {
        user,
        Tests
    }
        )=>{
    let {TestId} = useParams();
    let [Test, setTest] = useState({} as ITest)
    let history = useNavigate();
    useEffect(() => {
        let test = Tests.find(t=> t.id == Number(TestId));
        if(test == undefined) {
            alert("ошибка")
            history("/")
            return
        }
        setTest(test);
    }, [Tests]);
    
    
    let handlerFinishTest = ()=>{
        
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
                            <textarea name="ansver" id="que-answer" ></textarea>
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
    answer: string;
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