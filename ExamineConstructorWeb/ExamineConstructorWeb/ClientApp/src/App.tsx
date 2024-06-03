import React from 'react';
import './App.scss';
import { Route, Routes, useNavigate } from 'react-router-dom';
import { Register } from "./Register/Register";
import { Login } from "./Register/Login";
import { List } from "./List/List";
import { CreatePage } from "./CreatePage/CreatePage";
import {TestMenu} from "./TestMenu/TestMenu";

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
  
  
  const setBufUser = (data: IUserData) => {
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
        </Routes>
      </div>
  );
}

export default App;

interface ITest {
  id: number;
  name: string;
  questions_St: Array<IQuestion_st>;
  difficulty: number;
  authorid: number;
  description: string;
}
interface IQuestion_st {
  id: number;
  question: string;
  answer: string;
  difficulty: number;
}
