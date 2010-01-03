// $Id$
                                                                           
List Mixer
--------------------------------------------------------------------------------
Make presets for interactions that allow users to push Drupal data into a list.

Installation
____________
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


(This module is under active development - 12/30/2009)

About the module
----------------
List Mixer helps users of a Drupal website to manage methods of creating and 
updating lists of content. 

List Mixer works with fields, views and taxonomy. A site administrator can set
up any number of interaction presets. The interaction presets allow associations
of content types, fields, views, taxonomy terms, block ids and more to be 
connected up to a variety of ajax tools and storage methods.


How to Use ListMixer
--------------------

ListMixer is a module that allows you to set up a Drupal website in a way that lets you 
store data from a rendered drupal page into nodes. The intended use is to make lists of 
content, but there are probably some unique uses of ListMixer that will emerge.

ListMixer lets you create interaction presets. You supply the classes from a Drupal page
for a few different regions. 

You supply:
*An 'interaction div' - a container for your interaction controls and feedback.
*'source' - markup that will receive interaction behaviors
*'target' - will be a node id for a node that acts as the container for saved data.
*'target field' - where in a node data should be saved
*'behavior settings' - you can specify 'activate' 'interact' 'push' and 'submit' behaviors.
  *activate - a way that a page will become interactive (ex. a button)
  *interact - how your user can choose which data should be saved to the list (example. an input field that will store to a text field)
  *push - what format the data should be saved in (ex. name of a field)
  *submit - how your user can save data (ex. a 'submit button')
  
ListMixer requires
*a site with content
*you probably will want CCK, Views, Taxonomy installed
*you will probably want to have FireBug loaded into FireBug to figure out which data you are scraping.
*knowledge of jQuery very helpful for targeting complex data


Planned Features
*push: select field from a list (like in views) which will automatically store the field name and field type
*delete | edit: these are more dangerous and complicated so we'll be dealing with this later
*weight: make <ul> markup into re-weightable interactive. (like draggable views) (though, maybe if you have a view that is draggable, it will work anyways)
*tag content with a special token based term
*timestamp: a way of storing and accessing interaction history. probably just a watchdog setting with some sort of filter

Dangers
*Test your interactions well before installing on a production site.

Example

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

/*IN PROGRESS
target_nid = block id  - could be plaintext jQuery class definition. could be real jquery?

interactive div container = could (should be) a block, but doesn't have to be

sources = apply interact behavior to these classes

push_source = values from interact

push_target = machine name   nid + field name + type (checkbox + select fields like in views)

interact_source = from sources, interact sources evalutated to be true

activate button text

instructions

('taxonomy storage - it's not really storage, it's more about settings of how the interaction should work
so 'interaction storage is still sort of a correct term)

list-makin term = presetname + tokens -- if set, then invert the way that terms ar assigned,
instead of many to 1, it's 1 term to nodes or fields containing content that should be listed

preset delete -- will it delete the terms?
*/



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
  *'Babble' (included, in progress)
    Like DevSeed's 'shoutbox' module, which acts like Yammer - 
    intranet twitter. 
    Demonstrates of text field node saving to a list functionality.  
  *'Front Page Featured List' (not yet created)
    Just a simple list of things people might want on a homepage.
    There are about 10,000 ways to do this in Drupal already.
    *Demonstrates saving nodereferences to a list.    
  *'To-Do List' (not yet created)
    Provides a text field for adding items to a to-do list. 
    Provides list <li> and weight rearrangement to store reordered fields.
  *'Photo set' (not yet created)
    Provides a simple view + image content type that demonstrates adding 
    a checkbox to nodes and allows for subsets of a gallery view to be created 
    for many users, many lists. 
    Similar to Flickr Batch Organizer's functionality for making sets 
    from collections.
    
        
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
------------
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