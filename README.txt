All too often popular sites get flooded with useless comments which would be nice to hide by default from common visitors.
There are several comment moderation methods out there, but after careful examination it becomes apparent that Slashdot comment moderation system is superior to all: http://slashdot.org/moderation.shtml

This module implements some of the features of Slashdot moderation and commenting system.

The main benefits it's to have a self-moderating community where most relevant comments are highlighted and the other hidden to the user.

The module:
- Introdues Slashdot moderation system for node comments (troll, interesting, insightful, funny, etc)
- Collapses comments below selected threshold. Hidden comments can be expanded clicking on their title
- Allows fast moderation of multiple comments through AJAX
- Optionally Assigns karma to user based on how their comments are moderated by the community
- Determines initial score of new comments based on user karma
- Presents a vast set of ruels to determine who can moderate and limit abuses (i.e.: limited moderation points per user)
- Exports moderation information and user stats (i.e.: karma) to Views.
- Works with Advanced Forum allowing slashdot-like moderations on discussion boards
- Opens most of the settings to site administrators so that the behaviour of the module can be easily customized
