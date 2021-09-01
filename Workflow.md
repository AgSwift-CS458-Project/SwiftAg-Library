# Project Workflow

This document will cover the following:
  * Creating a working branch
  * Pushing to a working branch
  * Creating a pull request

Following this guide will help to prevent merge conflicts, and make development generally easier and more organized.
This assumes that you have Git already installed, and are using it on Powershell.

## Creating a Working Branch

To create a working branch, open a Powershell window and set the working directory to the main project folder (this would be the one that was created when you pulled the repository from GitHub)
Next, enter the command: 

`git checkout -b <username>-<issue/project being worked on>` 

Naming the branch should be based on your username and the issue or project being worked on; or, for general work, you could use something like `jaa177-working` as a branch title.

![Creating a working branch](https://github.com/AgSwift-CS458-Project/SwiftAg-Library/blob/main/docs_images/exbranch.png)

## Pushing to a Working Branch

To push to your working branch, first make sure to add and commit all changes using the following commands: 

`git add .`

`git commit -a -m "<message describing commit>"`

The message describing the commit can be short and doesn't have to be that descriptive.
When you've verified that the changes were committed, you can push the changes using:

`git push`

![Pushing changes to a working branch](https://github.com/AgSwift-CS458-Project/SwiftAg-Library/blob/main/docs_images/commitpush.png)

## Creating a Pull Request

Once you've pushed your changes to a working branch, you can open a Pull Request to have the changes incorporated into the main branch. 

To do this, open GitHub in your browser, navigate to the repository, and find your working branch. You should see a button saying "Compare and Pull Request", like so:

![Creating a pull request](https://github.com/AgSwift-CS458-Project/SwiftAg-Library/blob/main/docs_images/exampull.png)

This will automatically create a Pull Request which will request to merge the changes from your working branch to the main branch.

In the description of the pull request, describe in detail the changes made, including any references to issues being solved. Once that's done, click "Submit".

If given the option to merge the branches, **DO NOT CLICK MERGE.** It is very difficult to reverse changes to the main branch.

![Finishing the pull request](https://github.com/AgSwift-CS458-Project/SwiftAg-Library/blob/main/docs_images/examplepr.png)

Once you've submitted the request, you're done! Your pull request will be merged as soon as possible, unless changes are needed, which will be noted in the comments of the pull request.
