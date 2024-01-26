fof(allcreatedequal,axiom,(![H1,H2]:((human(H1)&human(H2))=>createdequal(H1,H2)))).
fof(john,axiom,(human(john))).
fof(johnfailed,axiom,(grade(john)=f)).
fof(someonegotana,axiom,(?[H]:(human(H)&grade(H)=a))).
fof(distinctgrades,axiom,(a!=f)).
fof(gradesnothuman,axiom,(![G]:~human(grade(G)))).
fof(someonenotjohn,conjecture,(?[H]:(human(H)&H!=john))).