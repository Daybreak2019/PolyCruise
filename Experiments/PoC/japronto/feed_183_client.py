import asyncio
import time
import aiohttp

NPARALLEL = 10000
aiohttp.TCPConnector(limit=100) 

async def fetch(session, i):
    async with session.post("http://127.0.0.1:9999/poc", data=f"POC testing message: session {i}") as response:
        data = await(result.content.read())
        print("result:", result, " - body:", data.decode())


async def fetch_all(loop):
    async with aiohttp.ClientSession(loop=loop) as session:
        results = await asyncio.gather(*[fetch(session, i) for i in range(NPARALLEL)])

if __name__ == '__main__':
    loop = asyncio.get_event_loop()
    loop.run_until_complete(fetch_all(loop))