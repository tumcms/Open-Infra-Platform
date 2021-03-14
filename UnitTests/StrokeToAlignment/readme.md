
### About Stoke To Alignment unit tests

Right now, one unit test is provided in the subfolder `001 Testsketch ArcClothoidStraight`, file `001 Testsketch ArcClothoidStraight.sketch`.<br/>
However, this unit test is not implemented in a source file until now.

#### How to use this unit test

- Start Open Infra Platform.<br/>
*NOTE:* You should change the size of the console. Make a right click on it, *properties*, tab *Layout*, 
region *Screen Buffer Size*, property *Height*. A value of at least 50 (or more) is recommended.
- Choose in the menu *Tools* the option *Convert Stroke to Alignment*.
- Choose the option *Load*.
- In the new dialog, navigate into the directory `C:\dev\Open-Infra-Platform\UnitTests\StrokeToAlignment\001 Testsketch ArcClothoidStraight\` 
(example, the root could be different), select the file `001 Testsketch ArcClothoidStraight.sketch`, and click *open*.
- The calculation could take a while. After it's done, the result is printed in the console window.
- Open the directory `C:\dev\Open-Infra-Platform\UnitTests\StrokeToAlignment\001 Testsketch ArcClothoidStraight\` in your default file explorer.
There you should find a file `001 Testsketch ArcClothoidStraight ResultExpected.txt` which includes the expected result.
To check whether the program works fine, just compare the content of this file with the output in the console window.
