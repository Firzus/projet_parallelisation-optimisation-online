'use client'

import React, { useState, useEffect } from 'react';

export default function Grid({
    dataGrid
}) {
    console.log(dataGrid);

    const [tokenPositions, setTokenPositions] = useState([
        ['', '', ''],
        ['', '', ''],
        ['', '', ''],
    ]);

    useEffect(() => {
        // Simuler un appel API
        const dataFromAPI = {
            "TokenPos": [
                "\u0000X\u0000",
                "\u0000O\u0000",
                "\u0000\u0000\u0000"
            ],
        };

        const tokenArray = dataFromAPI.TokenPos.map(row =>
            row.split('').map(token => (token === '\u0000' ? '' : token))
        );
        setTokenPositions(tokenArray);
    }, []);

    return (
        <div className="grid grid-cols-3 gap-1 w-fit">
            {tokenPositions.map((row, rowIndex) => (
                row.map((token, colIndex) => (
                    <div key={`${rowIndex}-${colIndex}`} className="w-20 h-20 bg-black flex justify-center items-center">
                        {token && (
                            <div className={`w-10 h-10 rounded-full ${token === 'X' ? 'bg-cyan-500' : 'bg-yellow-200'}`}></div>
                        )}
                    </div>
                ))
            ))}
        </div>
    );
};
