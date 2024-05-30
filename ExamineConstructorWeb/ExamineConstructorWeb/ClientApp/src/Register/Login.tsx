import react from 'react'
import './Register.scss'
import {NavLink} from "react-router-dom";

export const Login = ()=>{
    const [formData, setFormData] = react.useState({
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
        checkData(formData);
    }
    
    let checkData = async (data:any) => {
        await fetch("https://localhost:7148/api/login", {
            method: "POST",
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify(data)
        }).then(response => response.json())
            .then((data:IUserData) => {
                
                console.log(data);
            }).catch(error => {
                console.error(error);
            })
    }
    
    return (
        <div className="register-page">
            <h2>Login Page</h2>
            <form onSubmit={handleSubmit} className="login-form">
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
                <NavLink to={'/register'}>register</NavLink>
            </form>
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