import React from 'react';
import './TestMenu.scss';
import {useNavigate, useParams} from "react-router-dom";
import {IQuestion_st_Create, ITestCreate, ITestPass} from "../Interfaces";
import {Waiter} from "../Waiter/Waiter";

interface ITestMenuProps {}

export const EditTestMenu: React.FC<ITestMenuProps> = () => {
    let { TestId } = useParams();
    let [Test, setTest] = React.useState<ITestCreate>({} as ITestCreate);
    let [isLoad, setIsLoad] = React.useState(false);
    let history = useNavigate();

    React.useEffect(() => {
        setIsLoad(true);
        getTest();
    }, []);

    React.useEffect(() => {
        if (Test && Test?.questions_St?.length > 0) {
            setUpdateQuestions(new Array(Test.questions_St.length).fill(false));
            setUpdateAnswers(new Array(Test.questions_St.length).fill(false));
            setQuestions(Test.questions_St);
        }
    }, [Test]);

    const getTest = async () => {
        await fetch(`https://localhost:7148/api/Tests/test/${TestId}`, {
            method: "GET",
            headers: {
                'Content-Type': 'application/json',
                "Authorization": "Bearer " + localStorage.getItem("token")
            }
        }).then(response => response.json())
            .then((data: ITestCreate) => {
                if (data) {
                    setTest(data);
                } else {
                    history("/");
                }
                setIsLoad(false);
            })
            .catch(error => {
                setIsLoad(false);
                history("/");
                console.error(error);
            });
    }

    let [updateName, setUpdateName] = React.useState(false);
    let [Name, setName] = React.useState("");
    let [Description, setDescription] = React.useState("");
    let [updateDescription, setUpdateDescription] = React.useState(false);
    let [difficulty, setDifficulty] = React.useState(0);
    let [updateDifficult, setUpdateDifficult] = React.useState(false);
    let [updateQuestions, setUpdateQuestions] = React.useState<Array<boolean>>([]);
    let [updateAnswers, setUpdateAnswers] = React.useState<Array<boolean>>([]);
    let [Questions, setQuestions] = React.useState<Array<IQuestion_st_Create>>([]);

    const handleUpdateQuestion = (index: number, value: string) => {
        const newQuestions = [...Questions];
        newQuestions[index].question = value;
        setQuestions(newQuestions);
    }

    const handleUpdateAnswer = (index: number, value: string) => {
        const newQuestions = [...Questions];
        newQuestions[index].answer = value;
        setQuestions(newQuestions);
    }


    let handleSaveTest = async ()=>{
        setTest({...Test, questions_St: Questions, difficulty: difficulty, description: Description, name: Name})
        if(!checkValidData()) return;
        setIsLoad(true);
        await fetch(`https://localhost:7148/api/Tests/update/${TestId}`, {
            method: "PUT",
            headers: {
                'Content-Type': 'application/json',
                'Authorization': `Bearer ${localStorage.getItem("token")}`
            },
            body: JSON.stringify(Test)
        }).then(response => {
            setIsLoad(false);
            history(`/test/${TestId}`);
            if(response.status != 200){
                alert("Ошибка сохранения");
            }
        })
    }
    
    let checkValidData = ()=>{
        if(Test.name.length < 3){
            alert("Имя теста должно быть больше 3 символов");
            return false;
        }
        if(Test.description.length < 3){
            alert("Описание теста должно быть больше 3 символов");
            return false;
        }
        if(Test.difficulty < 0){
            alert("Сложность теста должна быть больше 0");
            return false;
        }
        for(let i = 0; i < Test.questions_St.length; i++){
            if(Test.questions_St[i].question.length < 3){
                alert("Вопрос должен быть больше 3 символов");
                return false;
            }
            if(Test.questions_St[i].answer.length < 3){
                alert("Ответ должен быть больше 3 символов");
                return false;
            }
        }
        return true;
    }

    return (
        <div className="update-test-page">
            {isLoad ? <Waiter /> : ""}
            <h1>Меню редактирования теста</h1>
            <h2>Нажните 2 раза ПКМ на поле которое хотите отредактировать</h2>
            <h2>Для сохранения нажмите <i>Enter</i>, или нажмите вне текстого поля</h2>
            <div className="test-description">
                {!updateName ? (
                    <h1
                        onDoubleClick={() => {
                            setUpdateName(true);
                            setName(Test.name);
                        }}
                    >Имя: {Test.name}</h1>
                ) : (
                    <input
                        type="text"
                        value={Name}
                        onChange={(e) => setName(e.target.value)}
                        onBlur={() => {
                            setUpdateName(false);
                            setTest({ ...Test, name: Name });
                        }}
                        onKeyPress={(e) => {
                            if (e.key === "Enter") {
                                setUpdateName(false);
                                setTest({ ...Test, name: Name });
                            }
                        }}
                    />
                )}

                {!updateDescription ? (
                    <h2
                        onDoubleClick={() => {
                            setUpdateDescription(true);
                            setDescription(Test.description);
                        }}
                    >описание {Test.description}</h2>
                ) : (
                    <textarea
                        value={Description}
                        onChange={(e) => setDescription(e.target.value)}
                        onBlur={() => {
                            setUpdateDescription(false);
                            setTest({ ...Test, description: Description });
                        }}
                        onKeyPress={(e) => {
                            if (e.key === "Enter") {
                                setUpdateDescription(false);
                                setTest({ ...Test, description: Description });
                            }
                        }}
                    />
                )}

                {!updateDifficult ? (
                    <h2
                        onDoubleClick={() => {
                            setUpdateDifficult(true);
                            setDifficulty(Test.difficulty);
                        }}
                    >Сложность: {Test.difficulty}</h2>
                ) : (
                    <input
                        type="number"
                        value={difficulty}
                        onChange={(e) => setDifficulty(Number(e.target.value))}
                        onBlur={() => {
                            setUpdateDifficult(false);
                            setTest({ ...Test, difficulty: difficulty });
                        }}
                        onKeyPress={(e) => {
                            if (e.key === "Enter") {
                                setUpdateDifficult(false);
                                setTest({ ...Test, difficulty: difficulty });
                            }
                        }}
                    />
                )}
            </div>
            <div className="test-questions">
                {Questions.map((question, index) => (
                    <div className="question-item" key={index}>
                        {updateQuestions[index] ? (
                            <textarea
                                placeholder="Вопрос"
                                value={question.question}
                                onChange={(e) => handleUpdateQuestion(index, e.target.value)}
                                onBlur={() => {
                                    const newUpdateQuestions = [...updateQuestions];
                                    newUpdateQuestions[index] = false;
                                    setUpdateQuestions(newUpdateQuestions);
                                }}
                                onKeyPress={(e) => {
                                    if (e.key === "Enter") {
                                        const newUpdateQuestions = [...updateQuestions];
                                        newUpdateQuestions[index] = false;
                                        setUpdateQuestions(newUpdateQuestions);
                                    }
                                }}
                            />
                        ) : (
                            <h2
                                onDoubleClick={() => {
                                    const newUpdateQuestions = [...updateQuestions];
                                    newUpdateQuestions[index] = true;
                                    setUpdateQuestions(newUpdateQuestions);
                                }}
                            >Вопрос: {question.question}</h2>
                        )}

                        {updateAnswers[index] ? (
                            <textarea
                                placeholder="Ответ"
                                value={question.answer}
                                onChange={(e) => handleUpdateAnswer(index, e.target.value)}
                                onBlur={() => {
                                    const newUpdateAnswers = [...updateAnswers];
                                    newUpdateAnswers[index] = false;
                                    setUpdateAnswers(newUpdateAnswers);
                                }}
                                onKeyPress={(e) => {
                                    if (e.key === "Enter") {
                                        const newUpdateAnswers = [...updateAnswers];
                                        newUpdateAnswers[index] = false;
                                        setUpdateAnswers(newUpdateAnswers);
                                    }
                                }}
                            />
                        ) : (
                            <h2
                                onDoubleClick={() => {
                                    const newUpdateAnswers = [...updateAnswers];
                                    newUpdateAnswers[index] = true;
                                    setUpdateAnswers(newUpdateAnswers);
                                }}
                            >Ответ: {question.answer}</h2>
                        )}
                        <div className="controls">
                            <button
                                onClick={() => {
                                    const newQuestions = [...Questions];
                                    newQuestions.splice(index, 1);
                                    setQuestions(newQuestions);
                                    setTest({...Test, questions_St: newQuestions});
                                }}
                                className={"delete-question"}
                            >Удалить
                            </button>
                        </div>
                    </div>
                ))}
                <button
                    className="add-question"
                    onClick={() => {
                        const newQuestions = [...Questions];
                        newQuestions.splice(newQuestions.length, 0, {
                            id: 0,
                            question: "Вопрос",
                            answer: "Ответ",
                            difficulty: 0
                        });
                        setQuestions(newQuestions);
                        setTest({...Test, questions_St: newQuestions});
                    }}
                >Добавить
                </button>
            </div>
            <div className="test-controlls">
                <button
                    className={"delete-test"}
                    onClick ={()=>{
                        setTest({}as ITestCreate);
                        history(`/test/${TestId}`);
                    }}
                >Отмена</button>
                <button
                    className={"update-test-button"}
                    onClick={handleSaveTest}
                    >Сохранить</button>
            </div>
        </div>
    );
}
