export default function Profile({
    playerName = "Default Player Name",
    playerToken = "Y",
    bgColor = "green"
}) {
    return (
        <section className="flex flex-col">
            <div className={`${bgColor == "green" ? "bg-player-two" : "bg-player-one"} h-12 rounded-t-3xl`} />

            <main className="flex p-8 gap-2 bg-neutral-900 rounded-b-3xl">
                <div className="flex flex-col gap-2 w-1/2">
                    <p className="text-neutral-50 whitespace-nowrap">
                        Player Name
                    </p>

                    <p className="text-neutral-400 truncate">
                        {playerName}
                    </p>
                </div>

                <div className="flex flex-col gap-2 w-1/2">
                    <p className="text-neutral-50 whitespace-nowrap">
                        Player Token
                    </p>

                    <p className="text-neutral-400 truncate">
                        {playerToken}
                    </p>
                </div>
            </main>
        </section>
    )
}