export default function TurnIndicator({
    currentPlayer = "Player Name",
    scorePlayerOne = 0,
    scorePlayerTwo = 0,
    isGameOver = false,
    winner = "Winner",
}) {
    return (
        <section className="rounded-full flex flex-col items-center gap-8 py-4 bg-neutral-900 w-full h-fit my-auto">
            {!isGameOver ?
                <p className="text-neutral-50">
                    C'est à <span className="text-neutral-400">{currentPlayer}</span> de jouer
                </p>

                :

                <p className="text-neutral-50">
                    C'est <span className="text-neutral-400">{winner}</span> qui gagne la partie
                </p>
            }

            <main className="flex">
                <p className="text-xl text-neutral-900 px-8 py-2 bg-player-one rounded-l-full font-semibold">
                    {scorePlayerOne}
                </p>

                <p className="text-xl text-neutral-900 px-8 py-2 bg-player-two rounded-r-full font-semibold">
                    {scorePlayerTwo}
                </p>
            </main>
        </section >
    )
}