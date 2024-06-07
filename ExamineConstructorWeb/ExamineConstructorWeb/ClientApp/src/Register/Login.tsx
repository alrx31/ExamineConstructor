import React, {useState} from 'react'
import './Register.scss'
import {NavLink, useNavigate} from "react-router-dom";
import {Waiter} from "../Waiter/Waiter";
import {IUserData, LoginData} from "../Interfaces";
export const Login = (
    {setUser = (data:IUserData) => {}}:any
)=>{
    let history = useNavigate();
    const [isLoad, setIsLoad] = useState(false);
    const [status, setStatus] = useState(0);
    const [formData, setFormData] = useState({
        login: '',
        password: ''
    })
    let handleChange = (event:any) =>{
        const {name, value} = event.target as HTMLInputElement;
        setFormData({
            ...formData,
            [name]: value
        })
    }
    let handleSubmit = (event:any) =>{
        event.preventDefault();
        setIsLoad(true);
        checkData(formData);
    }
    
    
    let checkData = async (data:any) => {
        await fetch("https://localhost:7148/api/Login", {
            method: "POST",
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(data)
        }).then(response => response.json())
            .then((data:LoginData) => {
                setIsLoad(false);
                if(data.token && data.user){
                    localStorage.setItem("token", data.token);
                    setUser(data.user);
                    history("/");
                }else{
                    setStatus(1); 
                    history("/login")
                }                
            }).catch(error => {
                setIsLoad(false);
                setStatus(1)
            })
    }
    
    return (
        <div className="register-page">
            {isLoad ? <Waiter/> : ""}
            <h2>Login</h2>
            <form onSubmit={handleSubmit} className={["login-form",status == 1 ? "error-form" : ""].join(' ')}>
                <div className="form-group">
                    <label htmlFor="login">Login</label>
                    <input
                        type="text"
                        id="login"
                        name="login"
                        onChange={handleChange}
                        value={formData.login}
                    />
                </div>
                <div className="form-group">
                    <label htmlFor="password">Password</label>
                    <input
                        type="password"
                        id="password"
                        name="password"
                        onChange={handleChange}
                        value={formData.password}
                    />
                </div>
                <button type="submit" className="login-button">Login</button>
                <NavLink to={'/register'}>Register</NavLink>
            </form>
        </div>
    )
}