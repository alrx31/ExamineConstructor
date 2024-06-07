import React, { useEffect, useState } from 'react';
import './List.scss';
import {NavLink, Route, Routes, useNavigate} from "react-router-dom";
import {TestMenu} from "../TestMenu/TestMenu";
import { IUserData, ITest } from '../Interfaces';

interface ListProps {
    user: IUserData;
    uptval: number;
    uptSelTests:(test:Array<ITest>)=>void; 
}

export const List: React.FC<ListProps> = (
    {
        user, 
        uptval,
        uptSelTests
    }
    ) => {
    const history = useNavigate();
    const [isLoad, setIsLoad] = useState(true);
    const [search, setSearch] = useState("");
    const [tests, setTests] = useState<ITest[]>([]);
    const [sortMethod, setSortMethod] = useState(1);
    const [delval, setDelVal] = useState(0);
    const [searchData, setSearchData] = useState<ITest[]>([]);
    
    useEffect(() => {
        setIsLoad(true);
        getAllTests();
    }, []);

    useEffect(() => {
        setIsLoad(true);
        getAllTests();
    }, [uptval]);

    useEffect(() => {
        if (!tests.length) return;
        let sortedTests = [...tests];
        if (sortMethod === 1) {
            sortedTests.sort((a, b) => a.difficulty - b.difficulty);
        } else if (sortMethod === 2) {
            sortedTests.sort((a, b) => b.difficulty - a.difficulty);
        } else if (sortMethod === 3) {
            sortedTests.sort((a, b) => a.name.localeCompare(b.name));
        } else if (sortMethod === 4) {
            sortedTests.sort((a, b) => b.name.localeCompare(a.name));
        }
        setSearchData(sortedTests);
    }, [sortMethod, tests]);

    useEffect(() => {
        if (search === "") {
            setSearchData(tests);
        } else {
            const filteredTests = tests.filter(test =>
                test.name.toLowerCase().includes(search.toLowerCase())
            );
            setSearchData(filteredTests);
        }
    }, [search, tests]);

    const getAllTests = async () => {
        try {
            const token = localStorage.getItem("token");
            if (!token) {
                // Обработка отсутствия токена, например, перенаправление на страницу логина
                console.error("No token found");
                return;
            }

            const response = await fetch("https://localhost:7148/api/Tests/tests", {
                method: "GET",
                headers: {
                    'Content-Type': 'application/json',
                    'Authorization': `Bearer ${token}`
                }
            });

            if (response.ok) {
                const data = await response.json();
                setIsLoad(false);
                setTests(data);
                setSearchData(data);
            } else {
                console.error("Failed to fetch tests, status: ", response.status);
                setIsLoad(false);
            }
        } catch (error) {
            setIsLoad(false);
            console.error(error);
        }
    }

    const handleCreateTestBut = () => {
        history("/create");
    }

    const handleDelete = async (id: number) => {
        try {
            await fetch(`https://localhost:7148/api/Tests/${id}`, {
                method: "DELETE",
                headers: {
                    'Content-Type': 'application/json',
                    'Authorization': `Bearer ${localStorage.getItem("token")}`
                }
            });
            getAllTests();
            setDelVal(delval + 1);
        } catch (error) {
            console.error(error);
        }
    }
    let handleSelectTest = (e:any) => {
        uptSelTests(searchData);
    }

    return (
        <div className={"List-page"} key={delval + uptval}>
            <div className="List-bar">
                <div className="custom-select">
                    <select
                        name="sort"
                        id="sort"
                        onChange={(e) => setSortMethod(Number(e.target.value))}
                    >
                        <option value="1">По сложности (возрастание)</option>
                        <option value="2">По сложности (убывание)</option>
                        <option value="3">По имени (по алфавиту)</option>
                        <option value="4">По имени (по алфавиту в обратном порядке)</option>
                    </select>
                </div>
                <input
                    type="text"
                    className={"search-bar"}
                    placeholder={"Поиск"}
                    onChange={(e) => setSearch(e.target.value)}
                />
                <button
                    className={"create-test"}
                    onClick={handleCreateTestBut}
                >Создать Тест
                </button>
            </div>

            <div className="list" key={uptval}>
                {isLoad ? "Загрузка..." : ""}
                {searchData.length ? searchData.map((elem, index) => (
                    <NavLink 
                        to={`/test/${elem.id}`}
                        key={index}
                        className={"list-item"}
                        onClick={handleSelectTest}
                    >
                        <h1>{index + 1}.</h1>
                        <h1>{elem.name}</h1>
                        <h3>Сложность: {elem.difficulty}</h3>
                        <h3>Описание: {elem.description}</h3>
                        <h3>Количество вопросов: {elem?.questions_St?.length}</h3>
                        <h3>Автор: {user.name}</h3>
                        <button
                            onClick={() => handleDelete(elem.id)}
                        >Удалить</button>
                    </NavLink>
                )) : <h1>Тесты не найдены</h1>}
            </div>
        </div>
    );
};