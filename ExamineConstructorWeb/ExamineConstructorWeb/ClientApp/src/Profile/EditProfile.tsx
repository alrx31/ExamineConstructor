import React, {useEffect} from 'react'
import './Profile.scss'
import {useNavigate, useParams} from "react-router-dom";
import {IUserData} from "../Interfaces";
import {Waiter} from "../Waiter/Waiter";

interface IEditProfileProps {
    thisUser: IUserData;
}
export const EditProfile:React.FC<IEditProfileProps> = ({
    thisUser
}) => {
    let {UserId} = useParams();
    let [user, setUser] = React.useState<IUserData>({} as IUserData);
    let [isLoad, setIsLoad] = React.useState(false);
    let history = useNavigate();
    let getUser = async () => {
        
        await fetch(`https://localhost:7148/api/User/${UserId}`,{
            method: "GET",
            headers: {
                'Content-Type': 'application/json',
                'Authorization': `Bearer ${localStorage.getItem("token")}`
            }
        }).then(response => response.json())
            .then((data:IUserData) => {
                setIsLoad(false)
                if(data){
                    setUser(data);
                }else{
                    alert("User not found");
                    history("/")
                }
                
            })
            .catch(error => {
                console.log(error);
                setIsLoad(false);
                history("/")
            })
    }
    
    
    useEffect(() => {
        setIsLoad(true);
        if(UserId==undefined || UserId==""){
            history("/")
        }
        getUser();
    }, []);
    
    let [editName, setEditName] = React.useState(false);
    
    let [editSurname, setEditSurname] = React.useState(false);
    let [editEmail, setEditEmail] = React.useState(false);
    let [editAge, setEditAge] = React.useState(false);
    
    let [editPassword, setEditPassword] = React.useState(false);
    let [editLogin, setEditLogin] = React.useState(false);
    let [secondPassword, setSecondPassword] = React.useState("");
    let handleSavaProfile = () =>{
        setIsLoad(true);
        if(user.name.length < 3){
            alert("Имя слишком короткое");
            setIsLoad(false);
            return;
        }
        if(user.surname.length < 3){
            alert("Фамилия слишком короткая");
            setIsLoad(false);
            return;
        }
        if(!vadilateEmail(user.email)){
            alert("Некорректный email");
            setIsLoad(false);
            return;
        }
        if(user.age < 1 || user.age > 120){
            alert("Некорректный возраст");
            setIsLoad(false);
            return;
        }
        if(user.login.length < 3){
            alert("Логин слишком короткий");
            setIsLoad(false);
            return;
        }
        if(user.password.length < 8 ) {
            alert("Пароль слишком короткий");
            setIsLoad(false);
            return;
        }
        if(user.password !== secondPassword){
            alert("Пароли не совпадают");
            setIsLoad(false);
            return;
        }
        sendProfile(user);
    }
    
    let sendProfile = async (user:IUserData)=>{
        await fetch(`https://localhost:7148/api/User/update/${user.id}`,{
            method: "PUT",
            headers: {
                'Content-Type': 'application/json',
                'Authorization': `Bearer ${localStorage.getItem("token")}`
            },
            body: JSON.stringify(user)
        }).then(response => {
            setIsLoad(false)
            if(response.ok){
                alert("Профиль успешно обновлен");
                history("/login")
            }else{
                alert("ошибка сервера");
                history("/")
            }
        }).catch(error => {
            alert("непредвиденная ошибка");
            setIsLoad(false);
            history("/")
        })
    }
    
    
    let vadilateEmail = (email:string) => {
        let re = /\S+@\S+\.\S+/;
        return re.test(email);
    }
    
    return (
        <div className={"edit-profile-page"}>
            {isLoad && <Waiter />}
            <h1>Радактирование профиля</h1>
            <div className="edit-profile-wrapper">
                <div className="edit-profile-item">
                    {editName ? (
                        <input 
                            type="text"
                            value={user.name}
                            onChange={(e) => setUser({...user, name: e.target.value})}
                            onSubmit={() => setEditName(false)}
                            onBlur={() => setEditName(false)}
                            onKeyPress={(e) => {
                                if(e.key == "Enter"){
                                    setEditName(false)
                                }
                            }}
                        />
                    ):(
                        <h2
                            onClick={() => setEditName(true)}
                        >Имя: {user.name}</h2>
                    )}
                    {editSurname ? (
                        <input
                            type="text"
                            value={user.surname}
                            onChange={(e) => setUser({...user, surname: e.target.value})}
                            onSubmit={() => setEditSurname(false)}
                            onBlur={() => setEditSurname(false)}
                            onKeyPress={(e) => {
                                if(e.key == "Enter"){
                                    setEditSurname(false)
                                }
                            }}
                        />
                    ):(
                        <h2
                            onClick={() => setEditSurname(true)}
                        >Фамилия: {user.surname}</h2>
                    )}
                    {editEmail ? (
                        <input
                            type="email"
                            value={user.email}
                            onChange={(e) => setUser({...user, email: e.target.value})}
                            onSubmit={() => setEditEmail(false)}
                            onBlur={() => setEditEmail(false)}
                            onKeyPress={(e) => {
                                if(e.key == "Enter"){
                                    setEditEmail(false)
                                }
                            }}
                        />
                    ):(
                        <h2
                            onClick={() => setEditEmail(true)}
                        >Почта: {user.email}</h2>
                    )}
                    {editAge ? (
                        <input
                            type="number"
                            value={user.age}
                            onChange={(e) => setUser({...user, age: Number(e.target.value)})}
                            onSubmit={() => setEditAge(false)}
                            onBlur={() => setEditAge(false)}
                            onKeyPress={(e) => {
                                if(e.key == "Enter"){
                                    setEditAge(false)
                                }
                            }}
                        />
                    ):(
                        <h2
                            onClick={() => setEditAge(true)}
                        >Возраст: {user.age}</h2>
                    )}
                    {editLogin ? (
                        <input
                            type="text"
                            value={user.login}
                            onChange={(e) => setUser({...user, login: e.target.value})}
                            onSubmit={() => setEditLogin(false)}
                            onBlur={() => setEditLogin(false)}
                            onKeyPress={(e) => {
                                if(e.key == "Enter"){
                                    setEditLogin(false)
                                }
                            }}
                        />
                    ):(
                        <h2
                            onClick={() => setEditLogin(true)}
                        >Логин: {user.login}</h2>
                    )}
                    {editPassword ? (
                        <div className={"input-wrapper"}>
                            <h2>Новый Пароль:</h2>
                            <input
                                type="password"
                                value={user.password}
                                onChange={(e) => setUser({...user, password: e.target.value})}
                                
                            />
                            <h2>Подтвердите пароль</h2>
                            <input
                                type="password"
                                value={secondPassword}
                                onChange={(e) => setSecondPassword(e.target.value)}
                                onSubmit={() => setEditPassword(false)}
                                onBlur={() => setEditPassword(false)}
                                onKeyPress={(e) => {
                                    if (e.key == "Enter") {
                                        setEditPassword(false)
                                    }
                                }}
                            />
                        </div>

                    ) : (
                        <h2
                            onClick={() => setEditPassword(true)}
                        >Пароль: </h2>
                    )}
                </div>
            </div>
            <div className="edit-profile-controlls">
                <button
                    onClick={() => history("/")}
                    className={"cancel-button"}
                >Отмена</button>
                <button
                    className={"save-button"}
                    onClick={handleSavaProfile}
                >Сохранить</button>
            </div>
            
            
        </div>
    )
}