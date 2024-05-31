import React from 'react';
import './App.scss';
import {Route, Routes, useNavigate} from 'react-router-dom'
import {Register} from "./Register/Register";
import {Login} from "./Register/Login";
import {Blocks} from "./Blocks/Blocks";
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
    ruleLevel: 1
  } as IUserData);
  
  const [page, setPage] = React.useState("" as string);
    
    React.useEffect(() => {
      if(user.ruleLevel == 2){
        console.log("admin");
        history("/admin");
      }else if(user.ruleLevel == 1){
        console.log("user");
        history("/");
      }else if(user.ruleLevel == 0){
        console.log("guest");
        history("/");
      }else{
        history("/login")
      }
      
    }, [user]);
  
  return (
    <div className="App">
      <h1>Конструктор экзаменационных билетов</h1>
      <h2>Добро пожаловать {user.name}</h2>
      
      
      
      <Routes>
        
        
        <Route path="/login" element={<Login setUser={setUser}/>} />
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
