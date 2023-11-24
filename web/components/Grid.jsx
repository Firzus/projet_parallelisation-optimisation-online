'use client'

import React, { useState, useEffect } from 'react';

export default function Grid({
    dataGrid
}) {
    const [tokenPositions, setTokenPositions] = useState([
        ['', '', ''],
        ['', '', ''],
        ['', '', ''],
    ]);

    useEffect(() => {
        const tokenArray = dataGrid.map(row =>
            row.split('').map(token => (token === '\u0000' ? '' : token))
        );
        setTokenPositions(tokenArray);
    }, []);

    return (
        <div className="grid grid-cols-3 gap-2">
            {tokenPositions.map((row, rowIndex) => (
                row.map((token, colIndex) => (
                    <div key={`${rowIndex}-${colIndex}`} className="w-32 h-32 bg-neutral-900 flex justify-center items-center">
                        {token && (
                            <div className={`w-16 h-16 rounded-full ${token === 'X' ? 'bg-player-two' : 'bg-player-one'}`}></div>
                        )}
                    </div>
                ))
            ))}
        </div>
    );
};
