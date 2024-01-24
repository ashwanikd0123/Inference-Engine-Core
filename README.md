# Inference-engine-core
basic command line inference engine based on first order logic

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

<h2>Domain Structure</h2>
<p />
In TPTP problems are divided in different domains based on the type of the problem it came from. following table indicates the classification.
<br />
<TABLE>
    <TR VALIGN=TOP>
        <TD> Logic
        <TD> Combinatory logic
        <TD>
        <TD> <TT>COL</TT>
    <TR>
        <TD>
        <TD> Logic calculi
        <TD>
        <TD> <TT>LCL</TT>
    <TR>
        <TD>
        <TD> Henkin models
        <TD>
        <TD> <TT>HEN</TT>
    <TR VALIGN=TOP>
        <TD> Mathematics
        <TD> Set theory
        <TD>
        <TD> <TT>SET</TT>, <TT>SEU</TT>, and <TT>SEV</TT>
    <TR>
        <TD>
        <TD> Graph theory
        <TD>
        <TD> <TT>GRA</TT>
    <TR>
        <TD>
        <TD> Algebra
        <TD> Relation algebra
        <TD> <TT>REL</TT>
    <TR>
        <TD>
        <TD>
        <TD> MV Algebras
        <TD> <TT>MVA</TT>
    <TR>
        <TD>
        <TD>
        <TD> Boolean algebra
        <TD> <TT>BOO</TT>
    <TR>
        <TD>
        <TD>
        <TD> Robbins algebra
        <TD> <TT>ROB</TT>
    <TR>
        <TD>
        <TD>
        <TD> Left distributive
        <TD> <TT>LDA</TT>
    <TR>
        <TD>
        <TD>
        <TD> Lattices
        <TD> <TT>LAT</TT>
    <TR>
        <TD>
        <TD>
        <TD> Quantales
        <TD> <TT>QUA</TT>
    <TR>
        <TD>
        <TD>
        <TD> Kleene algebra
        <TD> <TT>KLE</TT>
    <TR>
        <TD>
        <TD>
        <TD> Groups
        <TD> <TT>GRP</TT>
    <TR>
        <TD>
        <TD>
        <TD> Rings
        <TD> <TT>RNG</TT>
    <TR>
        <TD>
        <TD>
        <TD> Fields
        <TD> <TT>FLD</TT>
    <TR>
        <TD>
        <TD>
        <TD> Homological algebra
        <TD> <TT>HAL</TT>
    <TR>
        <TD>
        <TD>
        <TD> Real Algebra
        <TD> <TT>RAL</TT>
    <TR>
        <TD>
        <TD>
        <TD> General algebra
        <TD> <TT>ALG</TT>
    <TR>
        <TD>
        <TD> Number theory
        <TD>
        <TD> <TT>NUM</TT> and <TT>NUN</TT>
    <TR>
        <TD>
        <TD> Topology
        <TD>
        <TD> <TT>TOP</TT>
    <TR>
        <TD>
        <TD> Analysis
        <TD>
        <TD> <TT>ANA</TT>
    <TR>
        <TD>
        <TD> Geometry
        <TD>
        <TD> <TT>GEO</TT>
    <TR>
        <TD>
        <TD> Category theory
        <TD>
        <TD> <TT>CAT</TT>
    <TR VALIGN=TOP>
        <TD> Computer science
        <TD> Computing theory
        <TD>
        <TD> <TT>COM</TT>
    <TR>
        <TD>
        <TD> Knowledge representation
        <TD>
        <TD> <TT>KRS</TT>
    <TR>
        <TD>
        <TD> Natural Language Processing
        <TD>
        <TD> <TT>NLP</TT>
    <TR>
        <TD>
        <TD> Planning
        <TD>
        <TD> <TT>PLA</TT>
    <TR>
        <TD>
        <TD> Agents
        <TD>
        <TD> <TT>AGT</TT>
    <TR>
        <TD>
        <TD> Commonsense Reasoning
        <TD>
        <TD> <TT>CSR</TT>
    <TR>
        <TD>
        <TD> Semantic Web
        <TD>
        <TD> <TT>SWB</TT>
    <TR>
        <TD>
        <TD> Interactive Theorem Proving
        <TD>
        <TD> <TT>ITP</TT>
    <TR>
        <TD>
        <TD> Data Structures
        <TD>
        <TD> <TT>DAT</TT>
    <TR>
        <TD>
        <TD> Software creation
        <TD>
        <TD> <TT>SWC</TT>
    <TR>
        <TD>
        <TD> Software verification
        <TD>
        <TD> <TT>SWV</TT> and <TT>SWW</TT>
    <TR>
        <TD> Science and Engineering
        <TD> Biology
        <TD>
        <TD> <TT>BIO</TT>
    <TR>
        <TD>
        <TD> Hardware creation
        <TD>
        <TD> <TT>HWC</TT>
    <TR>
        <TD>
        <TD> Hardware verification
        <TD>
        <TD> <TT>HWV</TT>
    <TR>
        <TD>
        <TD> Medicine
        <TD>
        <TD> <TT>MED</TT>
    <TR>
        <TD>
        <TD> Processes
        <TD>
        <TD> <TT>PRO</TT>
    <TR>
        <TD>
        <TD> Products
        <TD>
        <TD> <TT>PRD</TT>
    <TR>
        <TD> Social sciences
        <TD> Social Choice Theory
        <TD>
        <TD> <TT>SCT</TT>
    <TR>
        <TD>
        <TD> Management
        <TD>
        <TD> <TT>MGT</TT>
    <TR>
        <TD>
        <TD> Geography
        <TD>
        <TD> <TT>GEG</TT>
    <TR>
        <TD> Arts and Humanities
        <TD> Philosophy
        <TD>
        <TD> <TT>PHI</TT>
    <TR>
        <TD> Other
        <TD> Arithmetic
        <TD>
        <TD> <TT>ARI</TT>
    <TR>
        <TD>
        <TD> Syntactic
        <TD>
        <TD> <TT>SYN</TT> and <TT>SYO</TT>
    <TR>
        <TD>
        <TD> Puzzles
        <TD>
        <TD> <TT>PUZ</TT>
    <TR>
        <TD>
        <TD> Miscellaneous
        <TD>
        <TD> <TT>MSC</TT>
</TABLE>