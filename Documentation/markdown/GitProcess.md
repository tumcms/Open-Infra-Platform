# Git Workflow

![](./fig/Git_Workflow.png)

Here you will find description about Git Workflow you need working with OpenInfraPlatform

## Prerequisites 

Before you can proceed to work with Git, there are several steps, which have to be done before Installation: 

1. Installation of **Git** - find [here](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git)
2. Creation of **GitHub account** - find [here](https://github.com/)

## Fork the repository

1. Go to OpenInfraPlatform on [GitHub](https://github.com/tumcms/Open-Infra-Platform).

2. Login to your account and *Fork* OpenInfraPlatform to your account. Now there is https://github.com/<your_username>/Open-Infra-Platform. 

3. *Clone* your repository to local mashine.

	- Open your File Explorer and select the folder, where you want to clone OpenInfraPlatform (e.g. C:\dev). Right mouse click in this folder and select *Git Bash Here*.

	- In the window, which you have opened, in the command line write out *git clone https://github.com/<your_username>/Open-Infra-Platform.git* . This will start a download.

4. Add remote: *git remote add tumcms https://github.com/tumcms/Open-Infra-Platform.git*

## Submit changes 

1. Before creating any changes, create new branch: 
 
	- Open OpenInfraPlatform folder and select *Git Bash Here*. You also can open **Git Bash** and write out in the command line *cd "<Path to OpenInfraPlatform>"* (e.g  *cd  "C:\dev\Open-Infra-Platform"*)

	- In the command line write out *git checkout -b <branchname>* (e.g *git checkout -b Fixing_Bugs*)

2. After creating some changes, *add* these changes:

	- In the command line of **Git Bash** write out *git add <filename>* to add changes to one file. 

	- **OR** write out -git add *- to add all changes you have made while working. 

3. *Commit* changes:

	- In the command line write out *git commit -m "Commit message"* (e.g. *git commit -m "Fixed Bugs"*)

4.*Push* changes to remote repository: 

	- In the command line write out *git push*

##Pull Request 

(Pull Request)

## Updating from main repository 

(Fetch all)...