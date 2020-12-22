# Notes on submission

This document presents notes and thoughts while reading the submission guidelines [here](https://joss.readthedocs.io/en/latest/submitting.html).

The answers are formatted as:

> Requirement from JOSS.

Our answer.

---
## Submission requirements

> * The software should be open source as per the OSI definition.

Yes, GPLv3.0 - see [licence](../../Licence.txt).

> * The software should have an obvious research application.

See list of publications made with the software [here](./paper.bib).

> * You should be a major contributor to the software you are submitting.

Observe [statistics](https://github.com/tumcms/Open-Infra-Platform/graphs/contributors).

> * Your paper should not focus on new research results accomplished with the software.

Ok, will not do that.

> * Your paper (paper.md and BibTeX files, plus any figures) must be hosted in a Git-based repository together with your software (although they may be in a short-lived branch which is never merged with the default).

See [here](https://github.com/tumcms/Open-Infra-Platform).

> In addition, the software associated with your submission must:
> * Be stored in a repository that can be cloned without registration.
> * Be stored in a repository that is browsable online without registration.
> * Have an issue tracker that is readable without registration.
> * Permit individuals to create issues/file tickets against your repository.

Hopefully the settings are correct.

> JOSS publishes articles about research software. This definition includes software that: solves complex modeling problems in a scientific context (physics, mathematics, biology, medicine, social science, neuroscience, engineering); supports the functioning of research instruments or the execution of research experiments; extracts knowledge from large data sets; offers a mathematical library, or similar.

I believe we fall under the term *engineering*, offering a *library*.

> Your software should be a significant contribution to the available open source software that either enables some new research challenges to be addressed or makes addressing research challenges significantly better (e.g., faster, easier, simpler).

Our software enables simultaneous loading of IFC as well as PCD data while being open source - we're not aware of any other open source library supporting the same.

> As a rule of thumb, JOSS’ minimum allowable contribution should represent not less than three months of work for an individual. Some factors that may be considered by editors and reviewers when judging effort include:
> * Age of software (is this a well-established software project) / length of commit history.

Project is already > 7 years old.

> * Number of commits.

We have > 1800 commits.

> * Number of authors.

Please see our [contributor list](../markdown/Contributors.md).

> * Total lines of code (LOC). Submissions under 1000 LOC will usually be flagged, those under 300 LOC will be desk rejected.

I don't know how to get this. Is there a tool that tells that quickly? Otherwise, my guess would be somewhere around 3 000 000 LOC. Look at the [statistics](https://github.com/tumcms/Open-Infra-Platform/graphs/contributors).

> * Whether the software has already been cited in academic papers.

See list of publications made with the software [here](./paper.bib).

> * Whether the software is sufficiently useful that it is likely to be cited by your peer group.

See list of publications made about the software [here](./paper.bib).

---
> In addition, JOSS requires that software should be feature-complete (i.e. no half-baked solutions) and designed for maintainable extension (not one-off modifications of existing tools). "Minor utility" packages, including "thin" API clients, and single-function packages are not acceptable.

TODO. This might be a bit tricky one. 
There are a lot of dangling parts (prototypical implementations from many students' projects). 

However, I believe that the core functionality is available and stable.
There are a lot of possibilities of expansion and further development.

---

## Submission flow


> * Make your software available in an open repository (GitHub, Bitbucket, etc.) and include an OSI approved open source license.

Done:

* [repository](https://github.com/tumcms/Open-Infra-Platform) 
* [licence](../../Licence.txt)

> * Make sure that the software complies with the JOSS review criteria. In particular, your software should be full-featured, well-documented, and contain procedures (such as automated tests) for checking correctness.

TODO.

> * Write a short paper in Markdown format using `paper.md` as file name, including a title, summary, author names, affiliations, and key references. See our [example paper](https://joss.readthedocs.io/en/latest/submitting.html#example-paper-and-bibliography) to follow the correct format.

TODO.

> * (Optional) create a metadata file describing your software and include it in your repository. We provide a script that automates the generation of this metadata.

What? I don't get it (yet).

## Review

**Possible revieweres**

Going through the list [here](https://joss.theoj.org/about#editorial_board), possible reviewers would be (name, reasons):

- Patrick Diehl (@diehlpk): C++, asynchronous and task-based programming 
- Hugo Ledoux (@hugoledoux): GIS, 3D geoinformation, computational geometry 
- Ben Stabler (@bstabler): Transportation systems, Urban data science, Geographic information systems (GIS)

Sadly, no experts can be located for these explicit topics:

- EXPRESS modelling language
- civil engineering field

**Review guidelines**

Needs review: [click here](https://joss.readthedocs.io/en/latest/review_checklist.html) and [here](https://joss.readthedocs.io/en/latest/review_criteria.html).

**Code of conduct**

For reference: [click here](https://github.com/openjournals/joss/blob/master/CODE_OF_CONDUCT.md).

