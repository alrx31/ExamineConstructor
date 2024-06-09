import react, {useState} from 'react';
import "./Register.scss"
import {Interface} from "node:readline";
import {NavLink, useNavigate} from "react-router-dom";
import {Waiter} from "../Waiter/Waiter";
import {IUserData} from "../Interfaces";
export const Register = (
    
) => {
    let history = useNavigate();
    const [isLoad, setIsLoad] = useState(false);
    const [status, setStatus] = useState(0);
    const [formData, SetFormData] = useState(
        {
            login:'',
            password:'',
            id: 0,
            name:'',
            surname: '',
            email: '',
            age: 0,
            ruleLevel: 1,
        } as IUserData
    )
    
    let handleSubmit = (event:any)=>{
        event.preventDefault();
        setStatus(0)
        
        if(formData.login == "" || formData.password == "" || formData.email == "" || formData.name == "" || formData.surname == "" || formData.age == 0){
            setIsLoad(false);
            setStatus(1);
            return;
        }
        
        
        sentData(formData);
    }
    
    let handleChange = (event:any) =>{
        setStatus(0)
        const {name, value} = event.target as HTMLInputElement;
        SetFormData({
            ...formData,
            [name]: value
        })
    }
    
    let sentData = async (data:IUserData) =>{
        await fetch("https://localhost:7148/api/register", {
            method: "POST",
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(data)
        }).then(response => response.json())
            .then(data => {
                setIsLoad(false);
                setStatus(2)
                history('/login')
            }).catch(error => {
                setIsLoad(false);
                setStatus(1)
                console.error(error);
            })
    }
    
    
    return (
        <div className="register-page">
            {isLoad ? <Waiter /> : ""}
            
            <h2>Регистрация</h2>
            <form onSubmit={(e) =>{handleSubmit(e);}} className={["register-form",status == 1 ? "error-form" : ""].join(" ")}>
                <div className="form-group">
                    <label htmlFor="login">Логин</label>
                    <input
                        type="text"
                        id="login"
                        name="login"
                        onChange={handleChange}
                        value={formData.login}
                    />
                </div>
                <div className="form-group">
                    <label htmlFor="password">Пароль</label>
                    <input
                        type="password"
                        id="password"
                        name="password"
                        onChange={handleChange}
                        value={formData.password}
                    />
                </div>
                <div className="form-group">
                    <label htmlFor="email">Почта</label>
                    <input
                        type="email"
                        id="email"
                        name="email"
                        onChange={handleChange}
                        value={formData.email}
                    />
                </div>
                <div className="form-group">
                    <label htmlFor="name">Имя</label>
                    <input
                        type="text"
                        id="name"
                        name="name"
                        onChange={handleChange}
                        value={formData.name}
                    />
                </div>
                <div className="form-group">
                    <label htmlFor="surname">Фамилия</label>
                    <input
                        type="text"
                        id="surname"
                        name="surname"
                        onChange={handleChange}
                        value={formData.surname}
                    />
                </div>
                <div className="form-group">
                    <label htmlFor="age">Возраст</label>
                    <input
                        type="number"
                        id="age"
                        name="age"
                        onChange={handleChange}
                        value={formData.age}
                    />
                </div>
                <button type="submit" className="register-button">Зарегистрировать</button>
                <NavLink to={'/login'}>Войти</NavLink>
            </form>
        </div>
    )
}