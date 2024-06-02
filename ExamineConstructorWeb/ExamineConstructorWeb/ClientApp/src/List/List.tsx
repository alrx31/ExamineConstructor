import React, {useEffect} from 'react';
import './List.scss';
import {useNavigate} from "react-router-dom";
export const List = (
    user:any,
    
    ) => {
    let history = useNavigate();
    const [isLoad, setIsLoad] = React.useState(true);
    const [search, setSearch] = React.useState("");
    const [Tests, setTests] = React.useState([] as Array<ITest>);
    const [sortMethod, setSort] = React.useState(1);

    useEffect(() => {
        setIsLoad(true);
        getAllTests();
    }, []);
    
    
    let getAllTests = async () => {
        await fetch("https://localhost:7148/api/gettests", {
            method: "GET",
            headers: {
                'Content-Type': 'application/json'
            }
        }).then(response => response.json())
            .then((data:Array<ITest>) => {
                setIsLoad(false);
                console.log(data);
                setTests(data);
            }).catch(error => {
                setIsLoad(false);
                console.error(error);
        })
    }
    
    useEffect(() => {
        if(sortMethod == 1){
            setTests(Tests.sort((a, b) => a.difficulty - b.difficulty));
        }else if(sortMethod == 2){
            setTests(Tests.sort((a, b) => b.difficulty - a.difficulty));
        }else if(sortMethod == 3){
            setTests(Tests.sort((a, b) => a.name.localeCompare(b.name)));
        }else if(sortMethod == 4){
            setTests(Tests.sort((a, b) => b.name.localeCompare(a.name)));
        }
    },[sortMethod]);
    
    let handleCreateTestBut = () => {
        history("/create");
        console.log("create test");
    }
    let handleChangeSearch = (e:any ) =>{
        console.log("search");
        setSearch(e.target.value)
        let newTests = Tests.filter((test) => {
            return test.name.toLowerCase().includes(e.target.value.toLowerCase());
        })
        setTests(newTests);
    }
    
    
    
    
    return (
        <div className={"List-page"}>
            <div className="List-bar">
                <div className="custom-select">
                    <select 
                        name="sort" 
                        id="sort"
                        onChange={(e) => setSort(+e.target.value)}
                    >
                        <option value="1" >По сложности (убывание)</option>
                        <option value="2">По сложности (возрастание)</option>
                        <option value="3">По имени (по алфавиту)</option>
                        <option value="4">По имени (по алфавиту в обратном)</option>
                    </select>
                </div>
                <input 
                    type="text" 
                    className={"search-bar"} 
                    placeholder={"Поиск"}
                    onChange={(e) => handleChangeSearch(e)}
                />
                <button 
                    className={"create-test"}
                    onClick={handleCreateTestBut}
                >Создать Тест
                </button>


            </div>
            <div className="sort-menu">

            </div>

            <div className="list">
                {isLoad ? "Загрузка..." : ""}
            </div>
        </div>
    );
};


interface IUserData {
    id: number;
    name: string;
    surname: string;
    email: string;
    age: number;
    login:string;
    password:string;
    ruleLevel: number;
}


interface ITest {
    id:number;
    name:string;
    questions_st: Array<IQuestion_st>;
    questions_gues: Array<IQuestion_gues>;
    difficulty:number;
    author_name:string;
    description:string;
}

interface IQuestion_gues{
    id:number;
    question:string;
    answers:Array<string>;
    rightAnswer:number;
    difficulty:number;
}

interface IQuestion_st{
    id:number;
    question:string;
    answer:string;
    difficulty:number;
}