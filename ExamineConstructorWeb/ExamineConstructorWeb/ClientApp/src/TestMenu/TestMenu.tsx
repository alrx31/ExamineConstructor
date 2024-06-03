import React from 'react';
import './TestMenu.scss';

interface ITestMenuProps {
    user:IUserData,
    Tests:ITest[]
}
export const TestMenu:React.FC<ITestMenuProps> = (
    {
     user, Tests
    }
) => {
    return (
        <div className={"TestMenu"}>
            test menu
        </div>
    );
};


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
