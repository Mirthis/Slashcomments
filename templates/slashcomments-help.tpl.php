<?php
//  $Id$

/**
 * @file
 */
?>

<div class="slashcomments-help">
This document will attempt to explain the moderation system that lies underneath the site commenting system. It will try to explain some of the history of the system, as well as how it works (or doesn't work) from both the perspective of the user, and the moderator.

<div id="toc">
<ul>
<li><a href='#toc_1'>Overview</a></li>
<ul>
<li><a href='#toc_1_1'>What’s up with this moderation thing?</a></li>
<li><a href='#toc_1_2'>Goals of moderation</a></li>
<li><a href='#toc_1_3'>Who can moderate?</a></li>
</ul>
<li><a href='#toc_2'>Karma</a></li>
<ul>
<li><a href='#toc_2_1'>What is Karma?</a></li>
<li><a href='#toc_2_2'>What is Karma good for?</a></li>
<li><a href='#toc_2_3'>Why is my Karma not what I expect?</a></li>
<li><a href='#toc_2_4'>How can I improve my Karma?</a></li>
<li><a href='#toc_2_5'>Is there a limit to how much Karma you can accumulate?</a></li>
</ul>
<li><a href='#toc_3'>Moderation</a></li>
<ul>
<li><a href='#toc_3_1'>How does the moderation work?</a></li>
<li><a href='#toc_3_2'>I just got moderator access, what do I do?</a></li>
<li><a href='#toc_3_3'>What is a Good Comment? A Bad Comment?</a></li>
<li><a href='#toc_3_4'>What do the choices in the moderation drop-down boxes mean?</a></li>
<li><a href='#toc_3_5'><?php print $moderations_points ?> non-cumulative points are not enough to moderate!</a></li>
<li><a href='#toc_3_6'>Why can't I suddenly moderate anymore?</a></li>
</ul>
<li><a href='#toc_4'>General questions</a></li>
<ul>
<li><a href='#toc_4_1'>What are thresholds?</a></li>
<li><a href='#toc_4_2'>Why don't you give moderators unlimited moderator access to <?php print $moderations_points ?> stories instead of giving them just <?php print $moderations_points ?> points?</a></li>
<li><a href='#toc_4_3'>I found a comment that was unfairly moderated!</a></li>
<li><a href='#toc_4_4'>Is this censorship?</a></li>
</ul>
</div>

<h2 id=toc_1>Overview</h2>

<h3 id=toc_1_1>What’s up with this moderation thing?</h3>
<p>
In every site with an active community, contentes get a lot of comments. A single story might have hundreds of replies- and let's be realistic: not all of the comments are that great. In fact, some are down right terrible, but others are truly gems.
<br/>
The moderation system is designed to sort the gems and the crap from the steady stream of information that flows through the pipe. And wherever possible, it tries to make the readers of the site take on the responsibility.
</p>
<p>
The goal is that each reader will be able to read the comments at the level they find appropriate. The impatient can read nothing at all but the original stories. Some will only want to read the highest rated comments, some will want to eliminate anonymous posts, and others will want to read every last drip of data, from the first post to the spam. The system will make that happen. Or at least, it sure will try...
</p>

<h3 id=toc_1_2>Goals of moderation</h3>

<ol>
<li><strong>Promote quality</strong>, discourage crap.</li>
<li><strong>Make the site as readable as possible</strong> for as many people as possible.</li>
<li><strong>Do not require a huge amount of time</strong> from any single moderator.</li>
<li><strong>Do not allow</strong> a single moderator's <strong>"reign of terror"</strong>.</li>
</ol>

<h3 id=toc_1_3>Who can moderate?</h3>

Any regular user is eligible to become a moderator. Deciding who is allowed to moderate is probably the most difficult part of the process. On one hand, many people say "Everyone", but we have chosen to avoid that path because the potential for abuse is so great. Instead, we set up a few simple rules for determining who is eligible to moderate.
<ol>
<li><strong>Logged in users</strong>: If the system can't keep track, it won't work, so you gotta log in. Sorry if you're paranoid, but this system demands a certain level of accountability.</li>
<li><strong>Positive contributors</strong>: the site tracks your "Karma" (see below), users with Karma 2 or more can moderate comments.</li>
</ol>

The following rules apply for the comments:
<ul>
<li><strong>If your Karma is 0 or -1</strong>, your comment will start with a 0 score. Anonymous Cowards start from 0. This weeds out spam accounts and trolls.</li>
<li><strong>If your Karma is 1</strong>, your comment will start with a 1 score.</li>
<li><strong>If your Karma is 2, 3, 4 or 5</strong>, your comment will start with a 2 score, and you will be able to moderate other comments (<?php print $moderations_points ?> moderation points per day).</li>
</ul>

So the end result is a pool of eligible users that (hopefully) represent average, positive contributors. 

<h2 id=toc_2>Karma</h2>

<h3 id=toc_2_1>What is Karma?</h3>

Your Karma is a reference that primarily represents how your comments have been moderated in the past. If a comment you post is moderated up, your Karma will rise. Consequently, if you post a comment that has been moderated down, your Karma will fall.

<h3 id=toc_2_2>What is Karma good for?</h3>

Karma is used to determine who moderates and who doesn't. Extremely bad Karma usually indicates a user account that is being used to spam the site.
<br/>
Secondly, users with better Karma are given a bonus point which can sometimes increase their comments initial score. Logged-in users normally post comments with a score of 1, but if a user earns higher Karma, they may post with a score of 2. Essentially it's a reward for being a good participant, or a punishment for being a bad one. Users with very low Karma might lose the +1 associated with being a logged-in user. Extremely bad users might even be penalized to a 0.

<h3 id=toc_2_3>Why is my Karma not what I expect?</h3>

If you've been moderating or posting, your Karma will likely fluctuate a little as you are moderated. Don't worry about it; this is normal. Please remember that this is just a number in a database that helps us determine who gets selected as a moderator. It doesn't determine your IQ or your value as a human being. It's simply not a big deal.

<h3 id=toc_2_4>How can I improve my Karma?</h3>

Here are some tips for improving your Karma:
<ol>
<li>
<strong>Post intelligently</strong>
Interesting, insightful, thought provoking comments are rated higher on a fairly consistent basis.
</li>
<li>
<strong>Post calmly</strong>
Nobody likes a flame war. In fact, more times than not the flamer gets burned much more than their target. "Flaim Bait" is hit quickly and consistently with "-1" by moderators. 
</li>
<li>
<strong>Post early</strong>
If an article has over a certain number of posts on it already yours is less likely to be moderated. This is, less likely both statistically (there are more to choose from) and due to positioning (a moderator has to actually find your post way at the end of a long list).
</li>
<li>
<strong>Stay on topic</strong>
Off topic posts are slapped quickly and consistently with "-1" by moderators.
</li>
<li>
<strong>Be original</strong>
Avoid being redundant and just repeating what has already been said. Yes, being moderated as "redundant" is worth "-1" to your post. Especially to be avoided are the "what he said" and "me too" posts.
</li>
<li>
<strong>Read it before you post</strong>
Does it say what you really want it to say? Check your own spelling and grammar. Occasionally, a perfectly beneficial post is passed over by moderators because of this completely irrelevant to content feature. This is also a good approach to checking yourself for what you're really saying.
</li>
<li>
<strong>Log in as a registered user</strong>
I know, this sounds obvious but, "Anonymous Coward" does not have a Karma rating. You can't reap the perceived benefits of your own accidental brilliance if you post anonymously. Have pride in your work and take credit for it.
</li>
</ol>

<h3 id=toc_2_5>Is there a limit to how much Karma you can accumulate?</h3>

Yes. Karma is now capped at 5. This was done to keep people from running up insane Karma scores, and then being immune from moderation. Despite some theories to the contrary, the Karma cap applies to every account.

<h2 id=toc_3>Moderation</h2>

<h3 id=toc_3_1>How does the moderation work?</h3>
<p>
When a moderator is given access, they are given a number of points of influence to play with. Each comment they moderate deducts a point. When they run out of points, they are done serving until the next day.
</p>
<p>
Moderation takes place by selecting an adjective from a drop down list that appears next to comments. Descriptive words like 'Flamebait' or 'Informative'. Bad words will reduce the comments score by a single point, good words increase a comments score by a single point. All comments are scored on an absolute scale from -1 to 5. Logged in users start at 1 (although this can vary from 0 to 2 based on their overall contribution to discussions).
</p>
<p>
<?php if($limit_take_part) : ?>
Moderators can not participate in the same discussion as both a moderator and a poster. This is to prevent abuses, and while it is one of the more controversial aspects of the system, we're sticking to it.
<?php endif; ?>
</p>
<p>
Concentrate more on promoting than on demoting. The real goal here is to find the juicy good stuff and let others read it. Do not promote personal agendas. Do not let your opinions factor in. Try to be impartial about this. Simply disagreeing with a comment is not a valid reason to mark it down. Likewise, agreeing with a comment is not a valid reason to mark it up. The goal here is to share ideas. To sift through the haystack and find needles. And to keep the children who like to spam in check.
</p>

<h3 id=toc_3_2>I just got moderator access, what do I do?</h3>
<p>
Moderate! Read comments (preferably at a low threshold) and when you see comments that are very insightful, or perhaps just plain off topic, select that option from the drop down list. When you are done, hit the 'Moderate' button. That's it!
</p>

<h3 id=toc_3_3>What is a Good Comment? A Bad Comment?</h3>

<ul>
  <li><strong>Good Comments are insightful</strong>. You read them and are better off having read them. They add new information to a discussion. They are clear, hopefully well written, or maybe amusing. These are the gems we're looking for, and they deserve to be promoted.</li>
  <li><strong>Average Comments might be slightly offtopic, but still might be worth reading</strong>. They might be redundant. They might be a 'Me Too' article. They might say something painfully obvious. They don't detract from the discussion, but they don't necessarily significantly add to it. They are the comments that require the most attention from the moderators, and they also represent the bulk of the comments. (Score: 0-1)</li>
  <li><strong>Bad Comments are flamebait</strong>. Bad comments have nothing to do with the article they are attached to. They call someone names. They ridicule someone for having a different opinion without backing it up with anything more tangible than strong words. Bad comments are repeats of something said 15 times already making it quite apparent that the writer didn't read the previous comments. They use foul language. They are hard to read or just don't make any sense. They detract from the article they are attached to.</li>
</ul>

<h3 id=toc_3_4>What do the choices in the moderation drop-down boxes mean?</h3>
<ul>
  <li><strong>Offtopic</strong> -- A comment which has nothing to do with the story it's linked to is Offtopic.</li>
  <li><strong>Flamebait</strong> -- Flamebait refers to comments whose sole purpose is to insult and enrage. If someone is not-so-subtly picking a fight (racial insults are a dead giveaway), it's Flamebait.</li>
  <li><strong>Troll</strong> -- A Troll is similar to Flamebait, but slightly more refined. This is a prank comment intended to provoke indignant (or just confused) responses. A Troll might mix up vital facts or otherwise distort reality, to make other readers react with helpful "corrections." Trolling is the online equivalent of intentionally dialing wrong numbers just to waste other people's time.</li>
  <li><strong>Redundant</strong> -- Redundant posts are ones which add no new information, but instead take up space with repeating information either in the post, the attached links, or lots of previous comments. For instance, some posters cut and paste otherwise legitimate comments in multiple places in the same discussion; the pasted versions are Redundant.</li>
  <li><strong>Insightful</strong> -- An Insightful statement makes you think, puts a new spin on a given story (or aspect of a story). An analogy you hadn't thought of, or a telling counterexample, are examples of Insightful comments.</li>
  <li><strong>Interesting</strong> -- If you believe a comment to be Interesting (and it's not mostly Redundant, Offtopic, or otherwise lame), it is.</li>
  <li><strong>Informative</strong> -- Often comments add new information to explain the circumstances hinted at by a particular story, fill in "The Other Side" of an argument, provide specifications to a product described too vaguely elsewhere, etc. Such comments are Informative.</li>
  <li><strong>Funny</strong> -- Think of Funny as being a good moderation choice if you actually think the comment is funny, not just because it seems intended to be. Not every knock-knock joke is Funny.</li>
  <li><strong>Overrated</strong> -- Sometimes you'll run into a comment which for whatever reason has been moderated out of proportion -- this probably means several moderators saw it at nearly the same time, thought it was Funny, Insightful etc, and their scores added together exaggerate its relative merit. (A knock-knock joke at +5, Funny) Such a comment is Overrated. It's not knocking the original poster to say so, but it's probably better to spend your mod points on comments which are deserving of being moderated up.</li>
  <li><strong>Underrated</strong> -- Likewise, some comments get smashed lower than they perhaps deserve by overzealous moderators. If you moderate a comment as Underrated, you're saying that it deserves to be read by more people than will see it at its current score. As with Overrated, if you can think of a more specific moderation reason, do so -- if a comment has already been moderated with an appropriate label though, and you just want to indicate that it deserves greater visibility, that's what Underrated is for. However, if a comment is labeled with a fitting (negative) label, choosing Underrated isn't such a great idea, because you could end up with contradictions like "+5, Flamebait."</li>
</ul>

<h3 id=toc_3_5><?php print $moderations_points ?> non-cumulative points are not enough to moderate!</h3>

On the contrary, they are probably too many. The reasoning is pretty simple: we don't want people to stockpile their points. We want people to use them or lose them. Otherwise people will hold on to their X points until a story comes on that they have a strong opinion in, and they will be tempted to moderate the discussion so as to sway things "their way". By expiring points every day, moderators are encouraged to use them. Sometimes their points might expire unused, but that’s OK: the system will just give points to someone else.

<h3 id=toc_3_6>Why can't I suddenly moderate anymore?</h3>
<?php if($limit_take_part) : ?>
You can't moderate and post in the same discussion.
<br/>
<?php endif; ?>
Do you still have any moderator points left? You only got <?php print $moderations_points ?>...

<h2 id=toc_4>General questions</h2>

<h3 id=toc_4_1>What are thresholds?</h3>

Your "threshold" is the minimum score that a comment needs to have if it is to be displayed to you. Comments are scored from -1 to 5, and you can set your threshold at any score within that range. So, for example, if you set your threshold at 2, only comments with scores of 2 or above would be displayed. Setting your threshold at -1 will display all comments. 0 is almost all comments. 1 filters out most Anonymous Cowards, and so on. Higher threshold settings reduce the number of comments you see, but (in theory, anyway) the quality of the posts you do see increases.

<h3 id=toc_4_2>Why don't you give moderators unlimited moderator access to <?php print $moderations_points ?> stories instead of giving them just <?php print $moderations_points ?> points?</h3>

It's a good question. Moderators' primary complaint is that they are often crippled by the tiny amount of points they have, and the overwhelming amount of comments that need moderation. If a good moderator could moderate all the comments in a given story, certainly that would be a great improvement.
The problem is that a single bad moderator could wreak havoc across those same <?php print $moderations_points ?> stories. By limiting the number of moderation points to <?php print $moderations_points ?>, any single moderator can only do so much damage. Sure they can only do so much *good* too, but that's the trade-off. we would rather see a hundred comments unmoderated than see a hundred comments moderated badly by some jerk with an axe to grind.

<h3 id=toc_4_3>I found a comment that was unfairly moderated!</h3>

Most of the time we've found that for every moderator out there pushing an agenda, there are a dozen good moderators making sure that everyone is getting a fair say. If you still think your comment was unfairly moderated, let us know and we'll look at it. Sometimes we might agree and revoke access to a moderator. Usually we disagree and let it go. It’s difficult to be the judge on this stuff since it is so subjective.

<h3 id=toc_4_4>Is this censorship?</h3>

We're not technically deleting anything. In fact "We" technically aren't really doing much at all. The masses are doing this for themselves (in theory anyway). And you are always given the option of clicking the threshold control over to '-1' and reading everything uncut, so we really have a hard time saying this truly is censorship. But if you really want to call it that, we can't really argue. We're trying to make as many people happy as possible here- if you don't like something, you can probably change it in the user preferences to more suit your tastes anyway.

Moderators are human beings, and human beings make mistakes. Still, moderators should try to be as thorough as they can. If there's a link in the comment, moderators should check it. If there are facts in the comment that a moderator knows to be wrong, he or she should take that into account. If the moderator doesn't know if the facts in a comment are correct or not, maybe the moderator should skip that comment.
</div>

