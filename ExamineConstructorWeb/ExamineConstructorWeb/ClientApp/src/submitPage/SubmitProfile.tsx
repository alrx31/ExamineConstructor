import React from 'react'
import {IUserData} from "../Interfaces";
import './Submit.scss'


interface ISubmitProfileProps {
    user:IUserData;
    setIsSubmitPage: React.Dispatch<React.SetStateAction<boolean>>
}


export const SubmitProfile:React.FC<ISubmitProfileProps> = ({
    user,setIsSubmitPage
    
}) => {
    
    let [code,setCode] = React.useState("");
    let handleSendData = (e:any) =>{
        e.preventDefault()




    }
    
    return (
        <div className={"submit-page"}>
            <form 
                className={"submit-form"}
                onSubmit={handleSendData}
            >
            <h2>Введите код подтверждения</h2>
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