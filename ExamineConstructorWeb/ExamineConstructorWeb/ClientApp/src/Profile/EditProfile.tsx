import React, {useEffect} from 'react'
import './Profile.scss'
import {useNavigate, useParams} from "react-router-dom";
import {IUserData} from "../Interfaces";
import {Waiter} from "../Waiter/Waiter";
import * as http2 from "http2";

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
                </div>
            </div>
        </div>
    )
}