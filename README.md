# bitlbee-dx

![](http://i.imgur.com/DSsES4E.png)

[![Build Status](https://travis-ci.org/dequis/bitlbee.svg?branch=wip%2Ftravis)](https://travis-ci.org/dequis/bitlbee)

This is an evil fork of BitlBee, using the evil platform known as 'github'.

Collecting random patches and breaking random stuff. Using [git-remote-bzr][] for bzr sync.

## Features

 * Git
 * Github
 * Skype
 * Facebook
 * Google Hangouts\*
 * Hipchat
 * Whatsapp\*
 * Telegram\*
 * Systemd integration
 * XML config
 * Mac OS X
 * Windows 8.1\*
 * Sublime text\*
 * mIRC scripts\*
 * Icechat\*
 * MS Comic chat\*
 * No selinux\*

_* Might not be implemented natively yet_

Features unique to this fork:

 * None (probably. check commit logs)

## Branches

 * `master`: follows upstream (was using `upstream` for this before)
 * `develop`: main bitlbee-dx branch.
 * `patch/*`: small patches and bugfixes (may be stolen from trac)
 * `feat/*`: non-trivial features
 * `<username>/*`: git mirrored branches of other people (like `flexo/python`)
 * `wip/*`: incomplete stuff.

## Workflow

This is a fork in the sense of a standalone project, but i'm also intending to
merge as much as possible upstream. Unfortunately upstream uses bzr, and bzr is
awful. Thanks to [git-remote-bzr][], most of this pain is avoided, but I've had
to do some compromises to keep this workflow.

Simple stuff first: features belong in feature branches, pull requests are used
for the review process. Travis-ci integration is enabled, but the test suite
isn't extremely comprehensive.

The develop branch diverges from master. Use `git cherry -v master` to compare
them. Commits that are in both branches are prefixed with a `-` (even if they
have different commit objects), while commits unique to develop are prefixed
with `+`

Upstream submission:

    git checkout -b branch-for-upstream master

    # cherry pick relevant commits, or fast-forward feature branches
    git cherry-pick CAFEBABE

    # TODO: figure out how to create a new remote bzr branch. i always forget

    # let git-remote-bzr know this branch exists
    git config remote.bzr-dequis.bzr-branches "upstream, branch-for-upstream"

    # push to bzr.dequis.org
    git push bzr-dequis branch-for-upstream

A fast forward is required so that `bzr pull` works, otherwise `bzr merge`
should be run, which generates a fat merge commit hiding all the commits in a
sub-timeline. Weird stuff.

Merging back from upstream:

    git fetch bzr-bitlbee
    git checkout master
    git merge bzr-bitlbee/master   # fast-forward

Then the commits from master are rebased to develop.

    git checkout -b master-rebase
    git rebase develop
    git checkout develop
    git merge master-rebase        # fast-forward
    git branch -d master-rebase

And this is why i say they diverge - all the commit objects are different.
I reserve the right of rebasing develop to clean up this mess to match upstream
at some point.

To handle .bzrignore as .gitignore in the bzr-only branches (which don't have
git specific stuff since they need to be sync'd perfectly with upstream)

    git config core.excludesfile .bzrignore

[git-remote-bzr]: https://github.com/felipec/git-remote-bzr
