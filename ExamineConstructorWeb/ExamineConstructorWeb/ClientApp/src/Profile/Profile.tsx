import React, {useEffect} from 'react';
import {useNavigate, useParams} from "react-router-dom";
import {IUserData} from "../Interfaces";
import {Waiter} from "../Waiter/Waiter";

interface IProfileProps {
    thisUser: IUserData;
}
export const Profile:React.FC<IProfileProps> = ({
    thisUser
})=> {
    let {UserId} = useParams();
    let [user, setUser] = React.useState({} as IUserData);
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
            }).catch(error => {
                console.log(error);
                setIsLoad(false);
                history("/")
            })
    }

    useEffect(() => {
        setIsLoad(true);
        getUser();
    }, []);
    
    
    return (
        <div className={"profile-page"}>
            {isLoad && <Waiter />}
            <div className="profile-wrapper">
                <h2>Профиль пользователя {user.name}</h2>
                <div className="profile-info">
                    <div className="profile-info-row">
                        <span>Имя:</span>
                        <span>{user.name}</span>
                    </div>
                    <div className="profile-info-row">
                        <span>Фамилия:</span>
                        <span>{user.surname}</span>
                    </div>
                    <div className="profile-info-row">
                        <span>Почта:</span>
                        <span>{user.email}</span>
                    </div>
                    <div className="profile-info-row">
                        <span>Возраст:</span>
                        <span>{user.age}</span>
                    </div>
                    <div className="profile-info-row">
                        <span>Логин:</span>
                        <span>{user.login}</span>
                    </div>
                    <div className="profile-info-row">
                        <span>Роль:</span>
                        <span>{user.ruleLevel}</span>
                    </div>
                </div>
            </div>
            <div className="profile-controlls">
                <button
                    onClick={() => history(`/`)}
                >Назад</button>
                {thisUser.id == user.id ?(
                    <button
                        onClick={() => history(`/user/update/${user.id}`)}
                    >Редактировать Профиль</button>
                ):("")
                        
                }
                
                
            </div>
        </div>
    );
}

