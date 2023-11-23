export async function getData() {
  const urlApi = "http://localhost:3001/data.json";
  const res = await fetch(urlApi, { cache: "no-store" });

  if (!res.ok) {
    throw new Error(`HTTP error! Status: ${res.status}`);
  }

  return res.json();
}

export default async function Home() {
  const data = await getData();
  console.log(data);
  return (
    <div className="bg-white">
      <main className="container flex flex-col gap-4 h-screen">
        <section>grid</section>
        <section className="flex gap-2">profile</section>
      </main>
    </div>
  );
}
