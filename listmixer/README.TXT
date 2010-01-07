// $Id$
                                                                           
List Mixer
--------------------------------------------------------------------------------
Make presets for interactions that allow users to push Drupal data into a list.

Version
-------
listmixer-0.1-dev
DEVELOPMENT VERSION, for demonstration purposes.

Installation
------------
To install place the entire listmixer module in your modules directory.
Go to Administer -> Site building -> Modules and enable the List Mixer module.

Go to Administer -> [admin/settings/listmixer] to configure settings.
Go to Administer -> [admin/build/listmixer] to make presets.

Git hub: git@github.com:chachasikes/List-Mixer.git
Web site: http://www.chachaville.com/content/list-mixer


Maintainer
-----------
Chach Sikes, chachasikes
http://drupal.org/user/50674

(Since 12/30/2009)

* NOTE: I am trying to apply for a Drupal CVS account with this module
to contribute it to drupal.org

How to Use ListMixer
--------------------

ListMixer lets you create 'interaction presets' that help a user
save data from a Drupal page into nodes.

ListMixer requires
*a site with content
*you probably will want CCK, Views, Taxonomy installed
*you will probably want to have FireBug loaded into FireBug to 
figure out which data you are scraping.
*knowledge of jQuery very helpful for targeting complex data
*javascript

An example:
The module is sort of abstract, so here is a description 
of what you can do with the module. When I finish a few
more features I will make a screencast of how to use it.


Babble:
So, you want to make an input box that lives on every page
of a Drupal site. Typing text into the box will save it
to a text field.

You can make this interaction without any more code than
a few jQuery class definitions. 

Demos
-----

In the /demos folder there are two demostrations that
work with the available behaviors. 

Babble and Photoset maker.



Brief overview of what you can do with the module
-------------------------------------------------

To create this, install and configure ListMixer.
Create a new ListMixer setting.

You then can choose different behaviors: 
Activate
Interact
Push
Submit


These behavior settings are used to connect markup
on a rendered Drupal page (you will probably not
be on the node edit page.) 


You then look at the page that is supposed to have 
the interactive text box, and find the #id of the block.
List Mixer lets you provide class definitions
that will connect parts of the page.

@TODO: Rename these containers to words that make sense.

They are:
Container: Where the submit button and help text 
should go

Target interaction id: jQuery compatible class
definition that will point to html containing the
nid of the node where the content should be stored.

Inclusions id: selectors that will receive interactive
elements (example, td in a views grid, or the container
if the interaction should be in the container.)

Source id: selector that will provide the node id or
other value information that should be saved. You 
will need to make sure that data is compatible with
the field you are trying to save it to.

Known issues and Bugs
---------------------
This module is very new. It works well if you only
have one enabled preset. Debugging the javascript
to allow multiple interactions on a given page.

Planned Features
----------------
*push: select field from a list (like in views) which will automatically store the field name and field type
*delete | edit: these are more dangerous and complicated so we'll be dealing with this later
*weight: make <ul> markup into re-weightable interactive. (like draggable views) (though, maybe if you have a view that is draggable, it will work anyways)
*tag content with a special token based term
*timestamp: a way of storing and accessing interaction history. probably just a watchdog setting with some sort of filter

Dangers
-------
*This is a development version of the site. Not recommended for 
production sites.


Example
-------
A good example of List Mixer in action is 'Babble' (see /demos)

Babble acts like Twitter, or DevelopmentSeeds 'Shoutbox' module. 
1. Set up Drupal environment.
  *You make a content type called 'BabbleStream.'
  *You create a views block that displays a user's BabbleStream.
  *You create a node of the type BabbleStream.
  *You enable that block on every page of the Drupal Site.
2. Make an interaction preset.
  *Then, you make it interactive using ListMixer.
  *You create a new ListMixer preset   /admin/build/listmixer
  *You choose 'Nodes' as the storage type.
  *Save.

3. Select Behaviors.

You will want:
  *Interact: Input (This will provide an input field) 
  *Activate: MouseDown (When you click on the Interact field, it will become active. The other options make you click a button to activate interactivity.)
  *Submit: Button (Create a button that will save your data.)
  *Push: field_text_babble, a text field in the content type BabbleStream. (Where and what kind of data are you storing to.)

4. Select Interaction.

These are the target and source fields and classes.



Updated 12-30-09

Organization of the module
--------------------------
*Demo (/demo)
  Demo contains an early prototype of this module which was created for a test
  writing workshop. It became obvious that the module should be abstracted 
  into something more useful, and so List Mixer is the resulting idea.
  
  *Interactions
  Interactions are the way that presets are stored, and List Mixer
  comes with some demonstrations of interactions.
  
  Examples:
  *'Babble' (included)
    Like DevSeed's 'shoutbox' module, which acts like Yammer - 
    intranet twitter. 
    Demonstrates of text field node saving to a list functionality.  
  *'Photo set' (almost there)
    Provides a simple view + image content type that demonstrates adding 
    a checkbox to nodes and allows for subsets of a gallery view to be created 
    for many users, many lists. 
    Similar to Flickr Batch Organizer's functionality for making sets 
    from collections.  
    
  *'Front Page Featured List' (not yet created)
    Just a simple list of things people might want on a homepage.
    There are about 10,000 ways to do this in Drupal already.
    *Demonstrates saving nodereferences to a list.    
  *'To-Do List' (not yet created)
    Provides a text field for adding items to a to-do list. 
    Provides list <li> and weight rearrangement to store reordered fields.

  * Other ideas...  
        
*List Mixer listmixer.module and includes (/includes)
  The actual listmixer module sets up the administration interface for list
  mixer. An important part of this is the preset generator.    
  
  *Presets (/includes/listmixer.presets.inc)
  Allow users to create presets for interactions. 
  
  For example, a user might pick a block that contains a view that shows
  a node that a user is allowed to edit on certain pages (ex. in a gallery.)
  The administrator can set a field, block id, and chose different methods
  for how interactions should take place, and on what. Whenever that block
  displays, it will contain javascript that is only allows to interact with
  certain content.

*Behaviors (/behaviors)
  Javascript library
  Various types of interactions provided to users. They are organized by
  the utilities they provide for interacting with drupal content.

  *NOTE: The folders in behaviors represent ideas for functions.
  The will be used for early javascript development (as includes)
  and then rolled into functions as appropriate as the module approaches
  a stable build.

  *listmixer.activate.js
   Functions that makes the content on a page ready for storing
   
  *listmixer.interact.js
   Functions that apply interaction elements to data that is allowed
   to be pushed or assigned a a list.
  
  *listmixer.push.js
   Functions that take data about a piece of content and convert it
   to a standarized format that Drupal node_save will accepts.
  
  *listmixer.submit.js
   Functions that trigger selected data to be pushed or assigned.


  Example of what behaviors do include:
    *when a button is clicked, turn all links on a site to 'storable'
    *create a checkbox on all drupal system images which will allow them 
      to be stored.
    *enable text to be selected on a site, selected text will be stored to a node
    *allow text input into a box, which will be stored to a node
    *create on/off button which will add or remove an item from a list
    *drag an item into or out of a list
    *rearrange items in a list
  
  
*Storage Systems (/storage)
  These are the various callback functions that take data from the
  ajax behavior functions and allow data to be created, loaded, updated
  and removed.
  
  The main storage systems include 'node' and 'taxonomy.' 
  *listmixer.node.inc
   Provides functions that prepare javascript data to be stored to 
   various types of content (nodes, fields, taxonomy terms.)
  *listmixer.taxonomy.inc
   Provides functions that generate special terms and vocabularies for
   lists, and will store those machine-generated terms in the node
   that should be listed.
   
  Storage systems is the area where callbacks that interact with other
  kinds of data would be stored. So, if someone wanted something to
  makes lists of comments, or users, or geo data...those could be added.
  Ideally, the callbacks would accept the data from all of the ajax functions.
  
  Examples of what can be accomplished with the storage systems:
    *store nodereferences
    *add links to a link field
    *store text to a text field
    *create interaction history (when an element was updated)
    *assign taxonomy term (machine term)
    *drop file into download bucket  
 
 
Support and Development plan
----------------------------
*This module requires Javascript. 

*Firefox 3.5+, Safari 4+, Internet Explorer 7+ will be supported.

*Initial development for proof of concept for Drupal 6, with most development
for Drupal 7 (and occasionally backporting to Drupal 6.)

*When this project has a Drupal page, will welcome discussion about how best
to design javascript functions and callbacks to work with existing tools.

*Will work on exporting presets, integrating with chaos tools, features 
and drush.

*Will determine what sort of hooks and api functions might allow widgets
and new field types to become available to the preset maker.