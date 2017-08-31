
Specifications
===========================
Max Money: 10 billion SSN;

Allocation: POW 8 billion SSN，POS 2 billion SSN (In one hundred years);

Block time: 64 seconds;

Block size: 1 M;

Difficulty retarget: every block;

Stake interest: 0.25% annually;

Min transaction fee: 0.0001 SSN，fees are paid to miners;

Confirmations: 10, pos maturity: 500;

Min stake age: 8 hours, no max age;

P2P port: 11201, RPC port: 11202;

Proof of work spec
Algo: scrypt;
Block reward: after 10 blocks, 0.0001 SSN, no halving;
Max height: 50000 (after this network will not accept PoW);
Proof of stake spec
Block reward: 0.25% annually, no halving;
Max height: no limit for one hundred years;


superskynet development tree

Development process
===========================

Developers work in their own trees, then submit pull requests when
they think their feature or bug fix is ready.

The patch will be accepted if there is broad consensus that it is a
good thing.  Developers should expect to rework and resubmit patches
if they don't match the project's coding conventions (see coding.txt)
or are controversial.

The master branch is regularly built and tested, but is not guaranteed
to be completely stable. Tags are regularly created to indicate new
stable release versions of superskynet.

Feature branches are created when there are major new features being
worked on by several people.

From time to time a pull request will become outdated. If this occurs, and
the pull is no longer automatically mergeable; a comment on the pull will
be used to issue a warning of closure. The pull will be closed 15 days
after the warning if action is not taken by the author. Pull requests closed
in this manner will have their corresponding issue labeled 'stagnant'.

Issues with no commits will be given a similar warning, and closed after
15 days from their last activity. Issues closed in this manner will be 
labeled 'stale'.
