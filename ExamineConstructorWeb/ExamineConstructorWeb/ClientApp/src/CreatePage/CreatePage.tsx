import React from 'react';
import "./CreatePage.scss";
import {useNavigate} from "react-router-dom";
import {Waiter} from "../Waiter/Waiter";

export const CreatePage = (
    user:any
) => {
    
    let history = useNavigate();
    const [isLoad, setIsLoad] = React.useState(false);
    const [isCreateStQuestion, setIsCreateStQuestion] = React.useState(false);
    const [test, setTest] = React.useState<ITest>({
        id: 0,
        name: "",
        questions_st: [] as Array<IQuestion_st>,
        difficulty: 0,
        author_id: user.id,
        description: ""
    } as ITest);
    const [question_st, setQuestion_st] = React.useState<IQuestion_st>({
        id: 0,
        question: "",
        answer: "",
        difficulty: 0
    } as IQuestion_st);
    const [questions_st, setQuestions_st] = React.useState<Array<IQuestion_st>>([] as Array<IQuestion_st>);

    let handleChangeQueSt = (e: React.ChangeEvent<HTMLInputElement>) => {  
        setQuestion_st({...question_st, [e.target.id]: e.target.value})
    }
    let HandleCreateQuestion = () => {
        setQuestions_st([...questions_st,question_st]);
        setQuestion_st({
            id: 0,
            question: "",
            answer: "",
            difficulty: 0
        });
        setIsCreateStQuestion(false);
    }
    
    let HandleCreateTest = () => {
        setTest({...test, questions_st: questions_st});
        
        if(test.name.length === 0){
            alert("Введите имя теста");
            return;
        }
        if(test.description.length === 0){
            alert("Введите описание теста");
            return;
        }
        if(test.difficulty === 0){
            alert("Введите сложность теста");
            return;
        }
        if(questions_st.length === 0){
            alert("Добавьте вопросы");
            return;
        }
        
        
        setIsLoad(true);
        sendTest(test);
    }
    
    let sendTest = async (test:ITest) => {
        /*console.log(JSON.stringify(test));
        await fetch("https://localhost:7148/api/Tests/addtest", {
            method: "POST",
            headers: {
                "Content-Type": "application/json"
            },
            body: JSON.stringify(test)
        }).then(response =>{
            /!*if(response.ok){
                setIsLoad(false);
                history("/");
            }
            else{
                alert("Ошибка при создании теста");
                setIsLoad(false)
            }*!/
        }).then(data => {
            console.log(data);
            setIsLoad(false);
        }).catch(error => {
            alert("Ошибк11111а при создании теста");
            setIsLoad(false)
        })*/
        setIsLoad(false);
    }
    
        return (
        <div className="create-page">
            {isLoad && <Waiter />}
            <div className="create-page-wrapper">
                <h1>Меню Создание Теста</h1>
                <div className="create-test">
                    <label htmlFor="name">Имя</label>
                    <input 
                        type="text" 
                        id="name"
                        placeholder={"Имя"}
                        onChange={(e) => setTest({...test,name: e.target.value})}
                    />
                    <label htmlFor="description">Описание</label>
                    <textarea id="description" placeholder={"Описание"}
                                onChange={(e) => setTest({...test, description: e.target.value})}
                    />
                    <label htmlFor="difficulty">Сложность</label>
                    <input type="number" id="difficulty" placeholder={"0"}
                            onChange={(e) => setTest({...test, difficulty: parseInt(e.target.value)})}
                    />

                    <div className="button-wrapper">
                        <button
                            className={"add-question-button"}
                            onClick={() => setIsCreateStQuestion(true)}
                        >Добавить вопрос
                        </button>
                    </div>

                </div>
                <div className="create-controll">
                    <button onClick={() => history("/")}>Отмена</button>
                    <button onClick={HandleCreateTest}>Создать</button>
                </div>
            </div>

            {
                isCreateStQuestion &&
                <div className="create-question">
                    <label htmlFor="question">Вопрос</label>
                    <input type="text" id="question" placeholder={"Вопрос"}
                        onChange={handleChangeQueSt}
                    />
                    <label htmlFor="answer">Ответ</label>
                    <input type="text" id="answer" placeholder={"Ответ"}
                        onChange={handleChangeQueSt}
                    />
                    <label htmlFor="difficulty">Сложность</label>
                    <input type="number" id="difficulty" placeholder={"0"}
                        onChange={handleChangeQueSt}
                    />
                    <div className="button-wrapper">
                        <button
                            className={"add-question-button"}
                            onClick={HandleCreateQuestion}
                        >Добавить
                        </button>
                        <button
                            className={"add-question-button error"}
                            onClick={() => setIsCreateStQuestion(false)}
                        >Отмена
                        </button>
                    </div>
                </div>
            }
            
            
            
            {
                questions_st.length > 0?
                    <div className="questions-list">
                        {questions_st.length > 0 &&
                            questions_st.map((question, index) => {
                                return (
                                    <div key={index} className="question">
                                        <p>{question.question}</p>
                                        <p>{question.answer}</p>
                                    </div>
                                )
                            })
                        }
                    </div> : null
            }
        </div>
    );
};


interface ITest {
    id: number;
    name:string;
    questions_st: Array<IQuestion_st>;
    difficulty:number;
    author_id:number;
    description:string;
}

interface IQuestion_st{
    id:number;
    question:string;
    answer:string;
    difficulty:number;
}