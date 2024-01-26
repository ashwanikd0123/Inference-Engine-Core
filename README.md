# Inference-engine-core
This project aims on developing a simple First order Inference or an Automated Theorem Prover (ATP) Engine From Scratch.<br>
The database that we are using for testing out ATP system is TPTP (Official www.tptp.org). which uses Syntax BNF for custom representation of First order formula described below.<br>
The original documentation can be collected from official page of TPTP.
I have also explained the Forst order formula syntax that our system is dealing with.

<h1>TPTP Syntax</h1>
<h2>Problem and Axiomatization Naming</h2>
A regular expression for recognizing problem file names is "[A-Z]{3}[0-9]{3}[-+^=_][1-9][0-9]*(\.[0-9]{3})*\.p". A regular expression for recognizing axiom file names is "[A-Z]{3}[0-9]{3}[-+^=_][1-9][0-9]*\.ax".
<br />
<br />
Problem file name:
<br />
DDD	NNN	F	V	.SSS	.T
<br />
DDD - Domain name abbreviation.
<br />
NNN - Abstract problem number. It is unique within the domain.
<br />
F   - Form. ^ for THF, _ for TFF without arithmetic, = for TFF with arithmetic, + for FOF, and - for CNF.
<br />
V   - Version number. It differentiates between different versions of the abstract problem.
<br />
SSS - Size parameter(s). These only occur for generated problems, and give the size parameter(s).
<br />
T   - File name extension. p for problem files, g for generator files.
<br />

<br />
Axiom file name
<br />
DDD	NNN	F	V	.TT
<br />
DDD - Domain name abbreviation.
<br />
NNN - Axiomatization number. It is unique within the domain.
<br />
F - Form. ^ for THF, _ for TFF without arithmetic, = for TFF with arithmetic, + for FOF, and - for CNF.
<br />
V - Specialization number. It identifies sets of axioms that are used to specialize an axiomatization. Axiomatizations of basic theories are allocated the number 0, and specialization axiom sets are numbered from 1 onwards.
<br />
T - File name extension. An extension is always ax.
<br />
<br />

<h2>Problem presentation</h2>
<h3>Header</h3>
<h4>file</h4>
The domain field identifies the domain, and possibly a subdomain, from which the problem is drawn. The domain corresponds to the first three letters of the problem name.

The % Problem field.
<h4>Domain</h4>
The domain field identifies the domain, and possibly a subdomain, from which the problem is drawn. The domain corresponds to the first three letters of the problem name.
<h4>Problem</h4>
This field provides a one-line, high-level description of the abstract problem. In axiom files, this field is called % Axioms, and provides a one-line, high-level description of the axiomatization.
<h4>Version</h4>
This field gives information that differentiates this version of the problem from other versions of the problem. The first possible differentiation is the axiomatization that is used. If a specific axiomatization is used, a citation is provided. If the axiomatization is a pure equality axiomatization (uses only the equal/2 predicate) then this is noted too.
<h4>English</h4>
This field provides a full description of the problem, if the one-line description in the % Problem field is too terse.
<h4>Refs</h4>
This field provides a list of abbreviated references for material in which the problem has been presented. Other relevant references are also listed. The reference keys identify BibTeX entries in the Bibliography.bib file supplied with the TPTP.
<h4>Source</h4>
This field acknowledges the source of the problem, usually as a citation. If the problem was sourced from an existing problem collection then the collection name is given in [ ] brackets.
<h4>Names</h4>
Problems that have appeared in other problem collections or the literature, often have names which are known in the ATP community. This field lists such names for the problem, along with the source of the name.
<h4>Status</h4>
This field gives the ATP status of the problem, according to the SZS problem status ontology. For THF, TFF, and FOF problems it is one of the following values.
<ol>
    <li>
        Theorem - Every model of the axioms (and other non-conjecture formulae, e.g., hypotheses and lemmas), and there are some such models, is a model of all the conjectures.
    </li>
    <li>
        ContradictoryAxioms - There are not models of the axioms (and other non-conjecture formulae, e.g., hypotheses and lemmas).
    </li>
    <li>
        CounterSatisfiable - Some models of the axioms (and there are some) are models of the negation of at least one of the conjectures.
    </li>
    <li>
        Unsatisfiable - There are no conjectures, and no interpretations are models of the axioms.
    </li>
    <li>
        Satisfiable - There are no conjectures, and some interpretations are models of the axioms.
    </li>
    <li>
        Unknown - The problem has never been solved by an ATP system.
    </li>
    <li>
        Open - The abstract problem has never been solved.
    </li>
</ol>

<h2>Syntax BNF</h2>
<h3>First order formula (fof) Syntax</h3>
First order formula is written as following syntax:</br>
<i>
fof(&lt;name&gt;,&lt;formula_role&gt;,&lt;fof_formula&gt;).
</i>
</br>

In the above syntax following is followed:
<ul>
<li><b>name:</b> name is just a unique string related to formula which indicates its source and other infos. this is not relavant to inference system.</li>
<li><b>formula_role:</b> this indicates the role of formula that has to be stored in knowledge base. in our case it could be an axiom or conjencture indicating its relation to the data given.</li>
<li><b>fof_formula</b>: this is the fof formula we need in inference system. its syntax will be explained in the next section.</li>
</ul>

<h3>First order formula Language</h3>
A 1st order language consists of three sets of symbols:
<ol>
<li>V is a set of <b>variables</b> (might be infinitely large).</li>
<li>F is a set of <b>Functors</b> each of which have an <b>arity</b>. The arity specifies the number of arguments they take (see below). Functors of arity 0 are constants.</li>
<li>P is a set of <b>predicate</b> symbols, each of which has an <b>arity</b>. Predicate symbols of arity 0 are propositions.</li>
</ol>
Rules:
<ul>
<li>Variable names always start with uppercase letters.</li>
<li>Functors and Predicates always start with lower case letters.</li>
<li>Functors and Predicates are distinguished by the context.</li>
</ul>

Two types of expressions are build from the above components of the language. Terms and Atoms.

<h4>Term</h4>
Terms are used to denote (possibly arbitrary) objects in the domain of interest. Terms thus correspond roughly to data in conventional programming. Terms are defined recursively by:
<ol>
<li>A functor of arity 0 (a constant) is a term</li>
<li>A variable is a term</li>
<li>A functor with the appropriate number of terms as arguments, is a term.
</ol>

<h4>Atom</h4>
The second type of expression is atoms, which correspond to the propositions of propositional logic. Atoms decribe relationships between terms (objects in the domain). Atoms are defined by:
<ol>
<li>A predicate symbol of arity 0 (a proposition) is an atom</li>
<li>A predicate symbol with the appropriate number of terms as arguments, is an atom.</li>
</ol>

<h4>Connectives</h4>
Connectives are used to combine atoms into the formulae of 1st order logic. The connectives include all those used in propositional logic, and two new quantifiers:
<ol>
<li>~ for negation.</li>
<li>& for conjunction.</li>
<li>| for disjunction.</li>
<li>=> for implication.</li>
<li><=> for equivalence.</li>
<li><~> for exclusive or (XOR).</li>
<li>! for universal quantification.</li>
<li>? for existential quantification.</li>
</ol>

The precedence order of the above operators is ! ? ~ | & => <=>, i.e., ! and ? bind most tightly, down to <=>.

<h4>Literals</h4>
Atoms and the negations of atoms are called literals.

<h4>Ground formulae</h4>
Ground formulae are formulae that contain no variables.

<h3>Equality</h3>
In many First order formulae equality among terms and predicates is present. To resolve these cases, the notion of equality must be introduced in the ATP.<br>
For this purpose we need to define equality axioms for out ATP to successfylly resolve these equalities.

<h4>Equality Axioms</h4>
Although the conjecture may seem like a logical consequence to humans, that's because humans "know" what equal means (even without knowing what the "maths" means). However, there are many models of the axioms that are not a models of the conjecture, e.g., simply by making even(sum(four,b)) be FALSE. Such models are possible because the axioms are missing definitions for equality. These definitions are the axioms of equality, and must be included to force equality to have its usual meaning. They are:
<ul>
<li><b>Reflexivity</b> - everything equals itself</li>
<li><b>Symmetry</b> - If X equals Y then Y equals X</li>
<li><b>Transitivity</b> - If X equals Y and Y equals Z, then X equals Z</li>
</ul>

Rules corresponding to above axioms are:
<ul>
<li>!X (X = X)</li>
<li>!X !Y (X = Y => Y = X)</li>
<li>!X !Y !Z ((X = Y & Y = Z) => X = Z)</li>
</ul>
<h4>References</h4>
<ul>
<li> www.tptp.org
<li> https://www.cs.miami.edu/home/geoff/Courses/CSC648-12S/Content/1stOrder.shtml#:~:text=Connectives%20are%20used%20to%20combine,%E2%88%A8%20or%20%7C%20for%20disjunction.
</ul>