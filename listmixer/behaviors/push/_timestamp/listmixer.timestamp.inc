<?php
// $Id$

/**
 * @file
 */

/*


i like the idea of allowing node revision to store interaction history
but

i would like a table that has timestamp information for interactions

ex. when a term was added to a node

this should maybe be a module since there will be a table
but it acts like a behavior

timestamp
id
user
list
type of content/module
type of interaction

maybe being able to pull/read from node revision history would be smart
but need a way to annotate the read for the difference - field updated
added to list

maybe each interaction needs a message - well, each behavior
maybe it's just a way of interacting with watchdog...settings messages
and then reading them. no need to make extra data tables.

what would be nice:
see when a term was added to a site (make a timeline)

string lines between them when content is added to the term (somehow)

messages like 'list rearranged' 'term added' 'content assigned to list'

i had some other idea about this a while back but i'm forgetting what it was



 */