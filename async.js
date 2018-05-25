async function sleepDo(ns, f)
{
    await new Promise((resolve) =>
    {
        setTimeout(resolve, ns);
    });
    f();
}
