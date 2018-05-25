async function sleepDo(ns, f){await new Promise(function(resolve){setTimeout(resolve, ns);});f();}
