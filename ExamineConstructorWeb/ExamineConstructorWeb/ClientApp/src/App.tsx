import React, {useEffect} from 'react';
import './App.scss';
import { Route, Routes, useNavigate } from 'react-router-dom';
import { Register } from "./Register/Register";
import { Login } from "./Register/Login";
import { List } from "./List/List";
import { CreatePage } from "./CreatePage/CreatePage";
import {TestMenu} from "./TestMenu/TestMenu";
import {StartTest} from "./TestMenu/StartTest";
import {ShowRaiting} from "./TestMenu/ShowRaiting";

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

const App: React.FC = () => {
  const history = useNavigate();
  const [user, setUser] = React.useState<IUserData>({
    id: 0,
    name: "",
    surname: "",
    email: "",
    age: 0,
    login: "",
    password: "",
    ruleLevel: -1
  });

  const [updateList, setUpdateList] = React.useState(0);
  const [Tests, setTests] = React.useState([] as Array<ITest>);
  
  const [Raiting, setRaiting] = React.useState({} as IRaiting);
  
  const setBufUser = (data: IUserData) => {
    if(data.login === 'admin') data.ruleLevel = 2
    else data.ruleLevel = 1;
    setUser(data);
  }
  

  React.useEffect(() => {
    if (user.ruleLevel === 2) {
      history("/admin");
    } else if (user.ruleLevel === 1) {
      history("/");
    } else if (user.ruleLevel === 0) {
      history("/");
    } else {
      history("/login");
    }
  }, [user]);

  useEffect(() => {
    // получения данных из cookie
    let user = localStorage.getItem("user");
    if (user) {
      setUser(JSON.parse(user));
    }
  }, []);

  const getUserId = () => user.id;
  const updateListFunc = () => setUpdateList(prev => prev + 1);
  
  
  let setTestProp = (test:Array<ITest>)=>{
    setTests(test);
  }

  return (
      <div className="App">
        <h1>Конструктор экзаменационных билетов</h1>
        <h2>Добро пожаловать {user.name}</h2>


        <Routes>
          <Route path="/" element={<List user={user} uptval={updateList} uptSelTests={setTestProp}/>} />
          <Route path="/login" element={<Login setUser={setBufUser} />} />
          <Route path="/register" element={<Register />} />
          <Route path="/create" element={<CreatePage updateList={updateListFunc} getUserId={getUserId} />} />
          <Route path="/test/:TestId" element={<TestMenu user={user} Tests={Tests}/>}/>
          <Route path="/pass/:TestId" element={<StartTest Tests={Tests} user={user} SetRaiting={setRaiting}/>}/>
          <Route path="/result/:RaitingId" element={<ShowRaiting Raiting={Raiting} />} />
        </Routes>
      </div>
  );
}

export default App;

interface ITest {
  id: number;
  name: string;
  questions_St: IQuestion_st[];
  difficulty: number;
  authorid: number;
  description: string;
}
interface IQuestion_st {
  id: number;
  question: string;
  difficulty: number;
}

interface IRaiting {
  "id": number,
  "userId": number,
  "user": string|null,
  "score": number,
  "testId": number,
  "test": string|null
}