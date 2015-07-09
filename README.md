![ArangoDB-Logo](https://www.arangodb.com/wp-content/uploads/2012/10/logo_arangodb_transp.png)

ArangoDB
========

1.4: [![Build Status](https://secure.travis-ci.org/arangodb/arangodb.png?branch=1.4)](http://travis-ci.org/arangodb/arangodb)
2.3: [![Build Status](https://secure.travis-ci.org/arangodb/arangodb.png?branch=2.3)](http://travis-ci.org/arangodb/arangodb)
2.4: [![Build Status](https://secure.travis-ci.org/arangodb/arangodb.png?branch=2.4)](http://travis-ci.org/arangodb/arangodb)
2.5: [![Build Status](https://secure.travis-ci.org/arangodb/arangodb.png?branch=2.5)](http://travis-ci.org/arangodb/arangodb)
Master: [![Build Status](https://secure.travis-ci.org/arangodb/arangodb.png?branch=master)](http://travis-ci.org/arangodb/arangodb)

ArangoDB is a multi-model, open-source database with flexible data models for documents, graphs, and key-values. Build high performance applications using a convenient SQL-like query language or JavaScript extensions. Use ACID transactions if you require them. Scale horizontally with a few mouse clicks.

The supported data models can be mixed in queries and allow ArangoDB to be the aggregation point for your data.

To get started, try one of our 10 minutes [tutorials](https://www.arangodb.com/tutorials) in your favourite programming language or try one of our [ArangoDB Cookbook recipes](https://docs.arangodb.com/cookbook).

For the impatient: [download](https://www.arangodb.com/download) and install ArangoDB. Start the server `arangod` and point your browser to `http://127.0.0.1:8529/`.

Key Features in ArangoDB
------------------------
* **Multi-Model**: Documents, graphs and key-value pairs — model your data as you see fit for your application.
* **Joins**: Conveniently join what belongs together for flexible ad-hoc querying, less data redundancy.
* **Transactions**: Easy application development keeping your data consistent and safe. No hassle in your client.

Here is an AQL query that makes use of all those features:

![AQL Query Example](https://www.arangodb.com/wp-content/uploads/2015/03/query_join.png)

Joins and transactions are key features for flexible, secure data designs, widely used in relational databases but lacking in many NoSQL products. However, there is no need to forego them in ArangoDB. You decide how and when to use joins and strong consistency guarantees, without sacrificing performance and scalability. 

Furthermore, ArangoDB offers a JavaScript framework called [Foxx](https://www.arangodb.com/foxx) that is executed in the database server with direct access to the data. Build your own data-centric microservices with a few lines of code:

Microservice Example

![Microservice Example](https://www.arangodb.com/wp-content/uploads/2015/03/microservice.png)

By extending the HTTP API with user code written in JavaScript, ArangoDB can be turned into a strict schema-enforcing persistence engine.

Next step, bundle your Foxx application as a [docker container](https://docs.arangodb.com/cookbook/UsingArangoDBNodeJSDocker.html) and get it running in the cloud.

Other features of ArangoDB include:

* **Schema-free schemata** let you combine the space efficiency of MySQL with the performance power of NoSQL
* Use a **data-centric microservices** approach with ArangoDB Foxx and fuse your application-logic and database together for maximal throughput
* JavaScript for all: **no language zoo**, you can use one language from your browser to your back-end
* ArangoDB is **multi-threaded** - exploit the power of all your cores
* **Flexible data modelling**: model your data as combination of key-value pairs, documents or graphs - perfect for social relations
* Free **index choice**: use the correct index for your problem, be it a skip list or a fulltext search
* Configurable **durability**: let the application decide if it needs more durability or more performance
* **Powerful query language** (AQL) to retrieve and modify data 
* **Transactions**: run queries on multiple documents or collections with optional transactional consistency and isolation
* **Replication** and **Sharding**: set up the database in a master-slave configuration or spread bigger datasets across multiple servers
* It is **open source** (Apache Licence 2.0)

For more in-depth information read the [design goals of ArangoDB](http://www.arangodb.com/2012/03/07/avocadodbs-design-objectives)


Latest Release - ArangoDB 2.6
-----------------

The [What's new in ArangoDB 2.6](https://docs.arangodb.com/NewFeatures/NewFeatures26.html) can be found in the documentation.

**New collection export HTTP REST API**: ArangoDB now provides a dedicated collection export API, which can take snapshots of entire collections more efficiently than the general-purpose cursor API. The export API is useful to transfer the contents of an entire collection to a client application.

Added **batch document removal and lookup** commands: The commands collection.lookupByKeys(keys) and collection.removeByKeys(keys) have been added for collection objects. These can be used to perform multi-document lookup and removal operations efficiently from the ArangoShell.

Added **AQL UPSERT command**: This adds an UPSERT statement to AQL that is a combination of both INSERT and UPDATE / REPLACE. The UPSERT will search for a matching document using a user-provided example. If no document matches the example, the insert part of the UPSERT statement will be executed. If there is a match, the update / replace part will be carried out.

We have **simplified the return value syntax** for data-modification AQL queries, added an **alternative implementation for AQL COLLECT** that uses a hash table for grouping and does not require its input elements to be sorted. 

Other **optimizations and speedups** in AQL relate to **subqueries**, **return values** and queries containing big **IN lists** for index lookups.

**Arangoimp** can now optionally update or replace existing documents, provided the import data contains documents with _key attributes.

**Foxx Improvements**

Added **Configuration and Dependencies** so that manifests can now define configuration options, as well as dependencies on other Foxx apps. With the **Mocha Test** framework you can now [write tests for your Foxx apps](https://www.arangodb.com/2015/04/testing-foxx-mocha/). The API documentation has been updated to **Swagger 2**. 



More Information
----------------

Please check the [Installation Manual](https://docs.arangodb.com/Installing/) for installation and compilation instructions.

The [User Manual](https://docs.arangodb.com/FirstSteps/) has an introductory chapter showing the basic operations of ArangoDB.


Stay in Contact
---------------

We really appreciate feature requests and bug reports. Please use our Github issue tracker for reporting them:

[https://github.com/arangodb/arangodb/issues](https://github.com/arangodb/arangodb/issues)

You can use the Google group for improvements, feature requests, comments 

[http://www.arangodb.com/community](https://www.arangodb.com/community)
