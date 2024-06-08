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
import { IUserData,ITest,IRaiting} from './Interfaces';
import {EditTestMenu} from "./TestMenu/EditTest";
import {Profile} from "./Profile/Profile";
import {EditProfile} from "./Profile/EditProfile";

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
    checkAuthToken().then((user) => {
      if (user) {
        setUser(user);
        history('/');
      } else {
        setUser({
          id: 0,
          name: "",
          surname: "",
          email: "",
          age: 0,
          login: "",
          password: "",
          ruleLevel: -1
        });
        history('/login');
      }
    });
  }, []);


  const getUserId = () => user.id;
  const updateListFunc = () => setUpdateList(prev => prev + 1);
  
  
  let setTestProp = (test:Array<ITest>)=>{
    setTests(test);
  }


  const checkAuthToken = async () => {
    const token = localStorage.getItem("token");

    if (!token) {
      return null;
    }

    try {
      const response = await fetch("https://localhost:7148/api/Login/validate-token", {
        method: "POST",
        headers: {
          'Content-Type': 'application/json',
          'Authorization': `Bearer ${token}`
        }
      });

      if (response.ok) {
        const user = await response.json();
        return user;
      } else {
        localStorage.removeItem("token");
        return null;
      }
    } catch (error) {
      localStorage.removeItem("token");
      return null;
    }
  };


  return (
      <div className="App">
        <h1>Конструктор экзаменационных билетов</h1>
        <h2>Добро пожаловать {user.name}</h2>
        <div className="app-profile-controll">
          <button
              className={"profile"}
              onClick={() => {
                history(`/user/${user.id}`);
              }}
            >Профиль
            </button>
          <button
              className={"log-out"}
              onClick={() => {
                setUser({} as IUserData);
                history("/login");
              }}
          >Выйти
          </button>

        </div>

        <Routes>
          <Route path="/" element={<List user={user} uptval={updateList} uptSelTests={setTestProp}/>}/>
          <Route path="/login" element={<Login setUser={setBufUser} />} />
          <Route path="/register" element={<Register />} />
          <Route path="/create" element={<CreatePage updateList={updateListFunc} getUserId={getUserId} />} />
          <Route path="/test/:TestId" element={<TestMenu user={user}/>}/>
          <Route path="/pass/:TestId" element={<StartTest Tests={Tests} user={user} SetRaiting={setRaiting}/>}/>
          <Route path="/result/:RaitingId" element={<ShowRaiting Raiting={Raiting} />} />
          <Route path="/update/:TestId" element={<EditTestMenu/>}/>
          <Route path="user/:UserId" element={<Profile thisUser={user} />} />
          <Route path="user/update/:UserId" element={<EditProfile thisUser={user} />} />
        </Routes>
      </div>
  );
}

export default App;