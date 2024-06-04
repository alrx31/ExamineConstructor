import React from 'react';
import './Download.scss';


interface IDownloadProps {
    
}

export const Download:React.FC<IDownloadProps> = () => {
    return (
        <div className={"Download"}>
            <h2>Скачать</h2>
            <div className="download-controll">
                <button
                    className={"download"}
                >Скачать</button>
            </div>
        </div>
    )
}