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
      <main className="container flex flex-col gap-8">
        <h1 className="text-neutral-50 mx-auto text-5xl pb-8 font-semibold">
          TicTacToe Board
        </h1>

        <section className="flex gap-8 justify-around">
          {/* Player One */}
          <Profile
            playerName={data.Player1.PlayerName}
            playerToken={data.Player1.PlayerToken}
            bgColor="beige"
          />

          {/* Turn */}
          <TurnIndicator
            currentPlayer={data.CurrentPlayer}
          // scorePlayerOne=""
          // scorePlayerTwo=""
          />

          {/* Player Two */}
          <Profile
            playerName={data.Player2.PlayerName}
            playerToken={data.Player2.PlayerToken}
            bgColor="green"
          />
        </section>

        <section className="">
          {/* Game Grid */}
          <Grid
            dataGrid={data.TokenPos}
          />
        </section>

      </main>
    </div>
  );
}
