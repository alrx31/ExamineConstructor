// данные пользователя 
export interface IUserData {
    id: number;
    name: string;
    surname: string;
    email: string;
    age: number;
    login: string;
    password: string;
    ruleLevel: number;
}

// данные о тесте
export interface ITest {
    id: number;
    name: string;
    questions_St: IQuestion_st[];
    difficulty: number;
    authorid: number;
    description: string;
}

// данные о вопросе
export interface IQuestion_st {
    id: number;
    question: string;
    difficulty: number;
}

// данные о прохождении теста
export interface IRaiting {
    "id": number,
    "userId": number,
    "user": string|null,
    "score": number,
    "testId": number,
    "test": string|null
}

// данные о прохождении (ответы на вопросы)
export interface IQue_pass {
    Id: number;
    Answer: string;
    "Difficulty":number
}

// данные о прохождении теста
export interface ITestPass {
    TestId: number;
    UserId: number;
    questions_St: Array<IQue_pass>;
    Difficulty: number;
}

// данные теста для создания
export interface ITestCreate {
    id: number;
    name: string;
    questions_St: IQuestion_st_Create[];
    difficulty: number;
    authorid: number;
    description: string;
}

// данные о вопросе при создании
export interface IQuestion_st_Create {
    id: number;
    question: string;
    answer: string;
    difficulty: number;
}


export interface LoginData{
    token:string;
    user:IUserData;
}