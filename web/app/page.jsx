import Grid from "@components/Grid";
import Profile from "@components/Profile";
import TurnIndicator from "@components/TurnIndicator";

export async function getData() {
  const urlApi = "http://localhost:3001/data.json";
  const res = await fetch(urlApi, { cache: "no-store" });

  if (!res.ok) {
    throw new Error(`HTTP error! Status: ${res.status}`);
  }

  return res.json();
}

export default async function Stats() {
  const data = await getData();

  return (
    <div className="h-screen bg-neutral-950 py-8">
      <main className="container flex flex-col gap-16 max-w-5xl">
        <h1 className="text-neutral-50 mx-auto text-4xl py-8 font-semibold">
          TicTacToe Board
        </h1>

        <section className="flex">
          {/* Turn */}
          <TurnIndicator
            currentPlayer={data.CurrentPlayer}
            winner={data.WinnerName}
          // scorePlayerOne=""
          // scorePlayerTwo=""
          />
        </section>

        <section className="flex gap-8 justify-between">
          <Grid dataGrid={data.TokenPos} />

          <div className="flex flex-col justify-between">
            {/* Player One */}
            <Profile
              playerName={data.Player1.PlayerName}
              playerToken={data.Player1.PlayerToken}
              bgColor="beige"
            // isConnect={data.Player1.IsConnect}
            />

            {/* Player Two */}
            <Profile
              playerName={data.Player2.PlayerName}
              playerToken={data.Player2.PlayerToken}
              bgColor="green"
            // isConnect={data.Player2.IsConnect}
            />
          </div>
        </section>
      </main>
    </div>
  );
}
