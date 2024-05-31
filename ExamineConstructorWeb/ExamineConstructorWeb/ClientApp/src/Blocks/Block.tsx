import React from 'react';
import './Blosks.scss';
export const Block = (
    setPage:any,
    icon:string,
    title:string,
    color:string
) => {
    return (
        <div
            className={"Block"}
            style={{backgroundColor: color}}
            onClick={setPage(title)}
        >
            <div className={"Icon"}>
                <img src={icon} alt={title}/>
            </div>
            <p className={"Title"}>{title}</p>
            
        </div>
    );
};

