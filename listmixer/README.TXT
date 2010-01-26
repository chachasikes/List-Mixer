// $Id$

ListMixer
---------
ListMixer allows you to add an interactive layer on top of 
rendered Drupal pages. A library of behaviors are available
which allow a user to store data out of the context of forms
and node-edit screen. See below for use cases.

This module is designed to allow users to create re-useable
settings that describe interactions.

Examples of interactions: 
*add an input field to a block that will save to a text field
 of a certain content type.

*drag select nodes and convert a list of terms into a pseudo-form.
provide a save button so that when clicked, terms will save
to all the selected nodes.

*make all links on a page interactive so they can be stored to
a content type that has a link field.


What is the module useful for?
------------------------------
* sites with a lot of content
* managing user-generated content
* remixing an archive into cherry-picked lists
* creating widgets for an intranet like site
* creating tools to quickly add content from an interface

Good to know
------------
An understanding of site configuration and themeing will be
beneficial. If you have that, then you should be able to do
some crazy awesome things with this module.


Version
-------
DEVELOPMENT VERSION, I will add this to Drupal CVS as soon as I can get a CVS account.

Installation
------------
To install place the entire listmixer module in your modules directory.
Go to Administer -> Site building -> Modules and enable the List Mixer module (API), User interface (UI), and  List Mixer Storage Type: Default (Nodes).

Go to Administer -> Site Configuration -> List Mixer Settings [admin/settings/listmixer] to configure settings.
Go to Administer -> User management -> Permissions -> [admin/build/listmixer] to set up permissions.
Go to Administer -> Site building -> List Mixer [admin/build/listmixer] to make presets.

Git hub: git@github.com:chachasikes/List-Mixer.git
Web site: http://www.chachaville.com/content/list-mixer

Demos
-----
GitHub List-Mixer page has a folder called 'demo', which contain working examples of ListMixer settings. (In development)

Maintainer
-----------
Chach Sikes, chachasikes
http://drupal.org/user/50674

(Development on this module began 12/30/2009)

Use cases
---------
* You can select nodes in a view and convert a
tagadelic block into 'taxonomy checkboxes' - clicking save
will add the terms to all of the selected nodes.

* You can add an input field to a block which will save to
a field in the content type of your choice, for a quick and 
simple 'twitter-like' interaction.

* You can display a list of nodes with multiple textfields
in a view. Click a button and sorting buttons will appear,
allowing you to rearrange your fields without visiting the
node-edit screen. This is similar to the 'to-do list' function
in Basecamp. You can apply this to any element (<li>, <td>, <div>).)
This means you can theme views and nodes and convert them to
interactives.

*You can show a view of photos in a photogallery. Click a 
button and checkboxes will be added to all of the photos.
Select the values and click save, and the nodereferences
to the photos can be saved into a 'photoset' content type.
Allowing you to make photo albums, and still use all of
the normal tools of drupal.

*You can add checkboxes to all of the links on a page, and
then store those links to a link field. This could be 
useful for making lists of paths to audio mp3 files that 
could then be then converted into an xml playlist.

*If you are a content administrator who has a large number
of pages to edit, you could use listmixer to create tools
that you can apply to all of your Drupal websites. For example,
if you had hundreds of photos and videos on a site, you
could make a view that shows tiny thumbnails and titles, and
another view that shows all the nodes that need content assigned
to them, and you could then click around on one page and edit
all of the nodes instead of going into the node-edit screen for
each one. This could be generic for all of your Drupal sites,
or customized for a particular project.

Normally it is way too much work to set up these tools and customize
ajax-based forms, but ListMixer is relatively quick to use.
You can create interactive content-editing tools for yourself
and your users.
(In progress: exporting presets as features.)

How it works
------------

ListMixer gives you certain tools, which you can combine to
invent new interactions.

Tools: Behaviors
----------------
Activate: Start your interaction with different tools
  *Currently available: 
  **Load: Start interaction on page load
  **Button: Click a button to activate the interaction
  **Select: Click or drag select the nodes that data will be stored into

Interact
  *Currently available:
  **Checkbox: Add a checkbox to whatever you want to be saved.
  **Input: Add an input field, whose data will be saved to your selected node.
  **Sort: Make elements on the page sortable (for example, the rendered contents of a plain text field.) 
    Saving will store the data rearranged.

Submit
  *Currently available:
  **Button: Click to save button.

Push
  *Nodereference: Save an nid to a nodereference field
  *Text: Save text to a text field
  *Link: Save a path to a link field
  *Term: Save terms to a node's taxonomy data


How to Use ListMixer User Interface
-----------------------------------

Screencasts
-----------
(currently out of date)

1. Introduction Demo: http://screencast.com/t/MjY5MzlmZGMt
Shows 'babble' and 'photoset_maker' in action

2. ListMixer User Interface Demo: http://screencast.com/t/ZjBmMmJk
Show the edit screens for babble and photoset_maker

3. 'Selectors' demo: http://screencast.com/t/ZDk3N2NmOWY
Talking a bit about finding/making jQuery compatible selectors using Firefox's Firebug extension 

Overview
--------
Step one: Think of what you want to make.
Step two: Configure your site, add content to site.
Step three: Download Firebug, or use 'Inspect Element' in safari. 


Things you will need
--------------------


1. An 'Interaction Design'
--------------------------
You will need to be able to state what you want to achieve.
Something like this:

I want all of my content editors to be able to see a list
of news feeds in a column on the left. They will also be 
able to see a column of recent photos. The interaction tool
will allow the editor to select a news story, and apply the image
to the news story. The goal is to speed up their process and
make the experience more pleasurable.

From this idea, you would figure out what parts you need.

Configuration you would need.

* a view showing news feeds
* a view showing photos
* news and photo content (both could come from feeds, or just
  normal content types)
* only allow content editors to see a page with two views

2. Listmixer widget settings
----------------------------
Then, you figure out what you will set up with Listmixer.

First, create a new listmixer and give is a name and
description. 

* Title:  Add photos to recent news items
* Activate: you want your user to select a node first
  Choose 'select'
* Input: you want a checkbox to show up on the photos
  Choose 'checkbox'
* Submit: you want a save button
  Choose 'submit button'
* Push: you want to store the node id of the photo node.
  Choose 'nodereference'

  You will use the name of the nodereference field in the news type.


Now, look at your page. You will have two views blocks on a page
(unless you have done some weird themeing)

Look at the page markup
-----------------------

*Listmixer uses the presence of CSS selectors to trigger the interactions.*

If you are already a themer, this is your lifeblood, so you 
may feel ecstatic that all you have to do is peek into Firebug to
see which elements you want to use. You will just enter them into
a form, add some labels if you like, click buttons to choose behaviors.
In a few minutes you will have set up an interaction.
 

Brief overview of CSS selectors and jQuery
------------------------------------------

If you are not a themer, here is a bit more explanation.
In brief, webpages have lots of 'containers' for all the content.
CSS targets those containers to apply colors, images, and spacing
which lays out your webpage.

These can have unique names (IDs) or reusable names (classes.)
These elements can also have attributes. 'href' in a normal
HTML link is an attribute.
<a href="http://mywebsite.com">Website</a>

Listmixer makes extensive use of these.

jQuery is the javascript library that comes with Drupal, and
it lets you select elements on a page if you tell it the right path.
It works a little differently from normal CSS that people write.
It requires that you give it your selector as well as the class.

div.field-item, not .field-item

jQuery accepts pseudo-classes. So, you can use any of these
to target anything on the page, even things generated on the page after
an interaction has started. (You can use listmixers own markup.)

Here's a trick that I have found handy in making listmixer settings.
Say you wanted to use a view that had a page display and an
attachment (two views on one page.)

You will notice that by default there are two div.view-contents
inside your view. This could screw up your interaction. You can use
div.view-myviewname(has:table.views-view-grid) to specify exactly which
element you want.


2. 'Targets'
------------

Target: the path to the node that you want to update.

Now for the magical moments. You want to identify your targets,
or which nodes you want data to be saved into.

Open firebug, and look at the view that contains news. You
want to grab the path to the node. Use the Firebug inspector
to select a node title. For the purposes of this demonstration,
the path to the href='content/news/disaster-haiti' is what you want.

So...there is a little bit of subtly to how to choose the elements
that will work for the 'Select' activation (but in my honest opinion
it is the coolest.)

For the "Selector: Target Node ID Value" you can do two things.
First, you can enter a straight up path to the link.

Like this:
div.view-photo-assigner div.view-content div.views-row div.views-field-title span.field-content a


How to select multiple targets
------------------------------
But!
The select feature is way fancier and super-cooler-awesomer.
So, I have set it up so that you can do a fancy little trick.

First, enter:
div.view-photo-assigner div.view-content

This is the parent container that contains the repeating elements that you will want
to select. 

Next, enter
Selector: Target Element Receiver: 
div.views-row div.views-field-title span.field-content a

This is the path to the link that has the path you want,
but it is just the part that repeats.

If this were a normal list:

Selector: Target Node ID Value: 
ul

Selector: Target Element Receiver: 
li a

Finally, since you do actually want the path, enter the name of the attribute
that contains the exact value that should be stored.

Selector: Target Value Attribute: 
href

If you leave this blank, Listmixer will assume that the html content inside
the Node ID or Element Receiver contains either the path or the node id value.

Like this,
Selector: Target Node ID Value: 
span.field-content

<span.field-content>253</span>

This will create a value of: 253

Listmixer converts a Drupal path to an nid value, ultimately you are trying
to find the path to the node that you want to update.

3. 'Sources'
------------
Ok, now that you understand the 'targets' - source will be easy. It's basically
the same thing, except you are finding the data that you actually want to store
into the node. The data needs to be compatible with the data that your node
accepts.


Nodereferences as sources
-------------------------
For example, if you are saving a nodereference, your source needs to be a
path to something in Drupal, or the number of the node id.

These would all work:
153
node/1241
content/blog/january-2010

Of course, you will need to make sure these are all valid, and that
your users can only target nodes that actually have a nodereference field
with the name that you set in your form. There are some permissions to
control who sees your ListMixer setting. 

Text as a source
----------------

Links as a source
-----------------

Terms as a source
-----------------


4. Last, but MOST IMPORTANT, a 'Container'
------------------------------------------
Listmixer looks for certain CSS elements to exist on a page. If it finds them,
it will add the interaction.

An easy example: if you have a block on a page, the block will have an ID. 
That ID will only live on pages with the block, which you can set up according 
to your own taste in roles, permissions etc.

You can actually have whatever you want. It could be the id for a node, the 
footer, content inside the contents of a node, something on a node edit screen.
If it is a class or ID, Listmixer will use it. 

** You will want your container to be unique **
You wouldn't want to use 'div.view-content' as your container unless you
were absolutely certain that you wanted an interaction to show up on
every single kind of view. Drupal will generate a unique class for your view
which you can use to good effect.



Why do this?
------------

This may take some getting used to if you are not familiar with building
Drupal sites, but its way easier than writing ajax functions and 
themeing forms, or shopping for modules that do something obscure. 

I think it is fun. You could create some bizarre interactions by combining
different pieces of drupal. It's also theoretically possible to make some 
simple interactions without needing to add a ton of modules.


For Developers
--------------
ListMixer provides and API which will allow you to create simple settings 
which will generate AJAX and interactive jQuery elements.

These are the main parts:
*Presets: settings that are passed to javascript. 
**These include the names of the behaviors to use, the css selectors that
jQuery should target, and the callback function paths that will handle
the data storage to Drupal.

API
---
See listmixer.api.php for implementations of available hooks.

It would be possible to write functions and modules that would generate
the markup that would be used by the main javascript file. For example,
if certain kinds of views and block settings are used to create interactions
you could write a module that takes a view name and field name and 
generate a preset. This would make it easier for site configurers to set
up interactions if they do not understand the Drupal markup.

Behaviors
---------
It is intended to make the behaviors extendable through code, though
there may be some limitations to how these actually work with the javascript.


User interface: settings storage
--------------------------------
It is theoretically possible to create other storage methods for saving the
listmixer preset settings. The default user interface form allows a user to
save every kind of value that is used by the main javascript file. 

Export/Import
-------------
Save your settings, provide custom presets.
Export/Import, hook_listmixer_default_preset, (and eventually drush/features exports)
