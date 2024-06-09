import React from 'react'
import {IUserData} from "../Interfaces";
import './Submit.scss'
import {useNavigate} from "react-router-dom";


interface ISubmitProfileProps {
    user:IUserData;
    setIsSubmitPage: React.Dispatch<React.SetStateAction<boolean>>
}


export const SubmitProfile:React.FC<ISubmitProfileProps> = ({
    user,setIsSubmitPage
    
}) => {
    let history = useNavigate();
    let [code,setCode] = React.useState("");
    let handleSendData = async (e:any) =>{
        e.preventDefault()
        await fetch("https://localhost:7148/api/Reset/reset", {
            method: "POST",
            headers: {
                'Content-Type': 'application/json',
                'Authorization': `Bearer ${localStorage.getItem("token")}`
            },
            body: JSON.stringify({
                ...user,
                "ConfirmCode": code
            })
        }).then(response => {
            if(response.ok){
                console.log("Профиль обновлен")
            }else{
                console.error("Не удалось обновить профиль")
            }
            history(`/user/${user.id}`);
            
        }).catch(error => {
            console.error(error);
        })
    }
    
    return (
        <div className={"submit-page"}>
            <form 
                className={"submit-form"}
                onSubmit={handleSendData}
            >
            <h1>Введите код подтверждения</h1>
                <h2>Отправлен на вашу почту</h2>
                <div className="form-group">
                    <input
                        type="text"
                        id="code"
                        name="code"
                        value={code}
                        onChange={(e) => setCode(e.target.value)}
                    />
                </div>
                <div className="form-controlls">
                    <button
                        type="submit"
                        className="submit-button"
                    >Подтвердить
                    </button>
                    <button
                        className="cancel-button"
                        onClick={() => setIsSubmitPage(false)}
                    >Отмена
                    </button>
                </div>

            </form>
        </div>
    )
}