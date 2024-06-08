import React, {useEffect} from 'react';
import "./CreatePage.scss";
import {useNavigate} from "react-router-dom";
import {Waiter} from "../Waiter/Waiter";
import {ITestCreate,IQuestion_st_Create} from "../Interfaces";

interface CreatePageProps {
    getUserId: () => number;
    updateList: () => void;
}

export const CreatePage:React.FC<CreatePageProps> = (
    {getUserId,updateList}
) => {
    let history = useNavigate();
    const [isLoad, setIsLoad] = React.useState(false);
    const [isCreateStQuestion, setIsCreateStQuestion] = React.useState(false);
    const [questions_st, setQuestions_st] = React.useState<Array<IQuestion_st_Create>>([] as Array<IQuestion_st_Create>);
    
    const [test, setTest] = React.useState<ITestCreate>({
        id: 0,
        name: "",
        questions_St: questions_st,
        difficulty: 0,
        authorid: getUserId(),
        description: ""
    } as ITestCreate);
    const [question_st, setQuestion_st] = React.useState<IQuestion_st_Create>({
        id: 0,
        question: "",
        answer: "",
        difficulty: 0
    } as IQuestion_st_Create);

    let handleChangeQueSt = (e: React.ChangeEvent<HTMLInputElement>) => {  
        setQuestion_st({...question_st, [e.target.id]: e.target.value})
    }
    let HandleCreateQuestion = (e:any) => {
        e.preventDefault();
        setQuestions_st([...questions_st,question_st]);
        setQuestion_st({
            id: 0,
            question: "",
            answer: "",
            difficulty: 0
        });
        setIsCreateStQuestion(false);
    }
    
    let HandleCreateTest = (e:any) => {
        e.preventDefault();
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
    
    let sendTest = async (test:ITestCreate) => {
        await fetch("https://localhost:7148/api/Tests/addtest", {
            method: "PUT",
            headers: {
                "Content-Type": "application/json",
                'Authorization': `Bearer ${localStorage.getItem("token")}`
            },
            body: JSON.stringify(test)
        }).then(response => {
            if (response.ok) {
                setIsLoad(false);
                history("/");
                updateList()
            } else {
                setIsLoad(false);
                alert("Ошибка при создании теста");
            }
        })
    }

    useEffect(() => {
        setTest({...test, questions_St: questions_st})
    }, [questions_st]);
    
    
        return (
        <div className="create-page">
            {isLoad && <Waiter />}
            <form
                className="create-page-wrapper"
                onSubmit={HandleCreateTest}
            >
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
                            type={"button"}
                            onClick={() => setIsCreateStQuestion(true)}
                        >Добавить вопрос
                        </button>
                    </div>

                </div>
                <div className="create-controll">
                    <button onClick={() => history("/")}>Отмена</button>
                    <button type={"submit"}>Создать</button>
                </div>
            </form>

            {
                isCreateStQuestion &&
                <form 
                    className="create-question"
                    onSubmit={HandleCreateQuestion}
                >
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
                            type={"submit"}
                        >Добавить
                        </button>
                        <button
                            className={"add-question-button error"}
                            onClick={() => setIsCreateStQuestion(false)}
                        >Отмена
                        </button>
                    </div>
                </form>
            }
            
            
            
            {
                questions_st.length > 0?
                    <div className="questions-list">
                        <h2>Список созданных вопросов</h2>
                        {questions_st.length > 0 &&
                            questions_st.map((question, index) => {
                                return (
                                    <div key={index} className="question">
                                        <p>Вопрос: {question.question}</p>
                                        <p>Ответ: {question.answer}</p>
                                        <p>Сложность: {question.difficulty}</p>
                                    </div>
                                )
                            })
                        }
                    </div> : null
            }
        </div>
    );
};
