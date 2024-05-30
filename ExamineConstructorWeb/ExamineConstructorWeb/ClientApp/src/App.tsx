import React from 'react';
import './App.scss';
import {Route, Routes, useNavigate} from 'react-router-dom'
import {Register} from "./Register/Register";
import {Login} from "./Register/Login";
function App() {
  let history = useNavigate();
  const [user, setUser] = React.useState({
    id: 0,
    name: "",
    surname: "",
    email: "",
    age: 0,
    login: "",
    password: "",
    ruleLevel: -1
  } as IUserData);
    
    React.useEffect(() => {
      if(user.ruleLevel == 2){
        console.log("admin");
        history("/admin");
      }else if(user.ruleLevel == 1){
        console.log("user");
        history("/u");
      }else if(user.ruleLevel == 0){
        console.log("guest");
        history("/g");
      }else{
        history("/login")
      }
      
    }, [user]);
  
  return (
    <div className="App">
      <Routes>
        <Route path="/login" element={<Login />} />
        <Route path="/register" element={<Register/>} />
      </Routes>
    </div>
  );
}

export default App;


interface IUserData {
  id : number;
  name:string;
  surname: string;
  email: string;
  age: number;  
  login:string;
  password:string;
  ruleLevel: number;
}
