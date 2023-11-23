async function getData() {
  const urlApi = "http://localhost:3001/data.json";
  const res = await fetch(urlApi, { cache: 'no-store' });

  if (!res.ok) {
      throw new Error(`HTTP error! Status: ${res.status}`);
  }

  return res.json()
}

export default async function Home() {
  const data = await getData();
  console.log(data);
  
  return (
    <main>
      app
    </main>
  )
}
