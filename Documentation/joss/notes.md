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

See list of publications made with OIP (TUM OpenInfraPlatform) [here](./paper.bib).

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

Our software enables simultaneous loading of IFC (Industry Foundation Classes) as well as Point Cloud Data (PCD) while being open source - we're not aware of any other open source library supporting the same.

> As a rule of thumb, JOSS’ minimum allowable contribution should represent not less than three months of work for an individual. Some factors that may be considered by editors and reviewers when judging effort include:
> * Age of software (is this a well-established software project) / length of commit history.

Project stated in 2013.

> * Number of commits.

We have > 1900 commits

> * Number of authors.

Please see our [contributor list](../markdown/Contributors.md).

> * Total lines of code (LOC). Submissions under 1000 LOC will usually be flagged, those under 300 LOC will be desk rejected.


1916 text files.
1776 unique files.                                          
396 files ignored.

github.com/AlDanial/cloc v 1.82  T=1.56 s (974.6 files/s, 428703.3 lines/s)

|Language              |       files      |    blank    |    comment    |       code
|----------------------|------------------|-------------|---------------|---------
|Expect                |          18      |    16693    |          0    |     134733|
|C++                   |         513      |    34279    |      43628    |     126259|
|C/C++ Header          |         458      |    20998    |      26319    |      95843|
|XSD                   |         105      |      113    |       1271    |      53205|
|C                     |          24      |     2796    |        664    |      17791|
|Qt                    |          32      |        0    |          0    |      10427|
|Bourne Shell          |           9      |      943    |       1628    |       9143|
|Qt Linguist           |           3      |        0    |          0    |       8663|
|XML                   |           9      |       38    |         14    |       8379|
|WiX source            |           2      |     3392    |         30    |       7278|
|m4                    |          17      |     1141    |         71    |       7018|
|SVG                   |          33      |       30    |         30    |       6275|
|Python                |          37      |     1997    |       2367    |       6077|
|MSBuild script        |          18      |        0    |         14    |       3316|
|CMake                 |          97      |      764    |       1743    |       2280|
|HLSL                  |          15      |      536    |        279    |       1620|
|XSLT                  |           4      |      153    |         81    |       1582|
|yacc                  |           1      |      317    |         20    |       1256|
|Markdown              |          18      |      445    |          0    |        957|
|HTML                  |           2      |       94    |        219    |        731|
|DOS Batch             |          32      |       69    |         63    |        666|
|Java                  |           1      |      138    |        293    |        634|
|make                  |          16      |      111    |         47    |        447|
|C#                    |          10      |       97    |         43    |        411|
|TeX                   |           2      |       92    |          1    |        402|
|lex                   |           1      |       31    |         23    |        250|
|Qt Project            |          32      |       90    |         16    |        234|
|QML                   |           2      |       10    |          4    |         57|
|ProGuard              |           8      |       31    |         30    |         57|
|MATLAB                |           1      |        5    |         13    |         24|
|JSON                  |           1      |        0    |          0    |         21|
|INI                   |           2      |        0    |          0    |          9|
|IDL                   |           1      |        0    |          0    |          1|
|----------------------|------------------|-------------|---------------|-----------|
|SUM:                  |        1524      |    85403    |      78911    |     506046|
|----------------------|------------------|-------------|---------------|-----------|


> * Whether the software has already been cited in academic papers.

See list of publications made with the software [here](./paper.bib).

> * Whether the software is sufficiently useful that it is likely to be cited by your peer group.

See list of publications made about the software [here](./paper.bib).

> In addition, JOSS requires that software should be feature-complete (i.e. no half-baked solutions) and designed for maintainable extension (not one-off modifications of existing tools). "Minor utility" packages, including "thin" API clients, and single-function packages are not acceptable.

There are a lot of dangling parts (prototypical implementations from many students' projects). 
These are well documented as issues, though.

I believe that the core functionality is available and stable.
There are a lot of possibilities of expansion and further development.


## Submission flow


> * Make your software available in an open repository (GitHub, Bitbucket, etc.) and include an OSI approved open source license.

Done:

* [repository](https://github.com/tumcms/Open-Infra-Platform) 
* [licence](../../License.txt)

> * Make sure that the software complies with the JOSS review criteria. In particular, your software should be full-featured, well-documented, and contain procedures (such as automated tests) for checking correctness.

The base functionality is there and is being constantly improved and extended.
I believe that the software will never be "done", there will always be possible additions, extensions, rework.

> * Write a short paper in Markdown format using `paper.md` as file name, including a title, summary, author names, affiliations, and key references. See our [example paper](https://joss.readthedocs.io/en/latest/submitting.html#example-paper-and-bibliography) to follow the correct format.

[Done](./paper.md).

> * (Optional) create a metadata file describing your software and include it in your repository. We provide a script that automates the generation of this metadata.

What? We don't get it (yet).

## Review

**Possible revieweres**

Going through the list [here](https://joss.theoj.org/about#editorial_board), possible reviewers would be (handle: reasons):

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

