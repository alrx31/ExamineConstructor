import React from 'react';
import './Raiting.scss';
import {useNavigate, useParams} from "react-router-dom";
import {IRaiting} from "../Interfaces";

interface IUserData {
    Raiting: IRaiting
}

export const ShowRaiting: React.FC<IUserData> = ({
    Raiting
}) => {
    let {RaitingId} = useParams();
    let history = useNavigate();
    
    if(Raiting.id !== Number(RaitingId)) {
        alert("ошибка");
        history("/");
    }
    
    
    return (
        <div className="raiting-page">
            <h1>Результат</h1>
            <div className="raiting">
                <div className="raiting__user">
                    <h2>Пользователь: {Raiting.userId}</h2>
                </div>
                <div className="raiting__score">
                    <h2>Оценка: {Raiting.score}</h2>
                </div>
                <div className="raiting__test">
                    <h2>Тест: {Raiting.testId}</h2>
                </div>
            </div>
            <div className="result__controlls">
                <button
                    onClick={()=>history("/")}
                >На главную</button>
                <button
                    onClick={()=>history("/test/"+Raiting.testId)}
                >Назад</button>
            </div>
        </div>
    )
}