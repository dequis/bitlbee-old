# bitlbee-dx

![](http://i.imgur.com/DSsES4E.png)

[![Build Status](https://travis-ci.org/dequis/bitlbee.svg?branch=wip%2Ftravis)](https://travis-ci.org/dequis/bitlbee)
[![Coverity Scan Build Status](https://scan.coverity.com/projects/3287/badge.svg)](https://scan.coverity.com/projects/3287)

This is an evil fork of BitlBee, using the evil platform known as 'github'.

Collecting random patches and breaking random stuff. Using [git-remote-bzr][] for bzr sync.

Mappings of bzr revisions to git commits are available here: [html][], [raw][] (created using [git-bzr-rev-map][])

Arch linux PKGBUILD available in the [AUR][], because if you don't have an arch
package you're clearly not evil enough.

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
 * Arch Linux support
 * American english support

_* Might not be implemented natively yet_

Interesting features unique to this fork:

 * None (probably. check commit logs)

## Pull requests

Pull requests to this repository are used for code review - often for my own
branches.

Feel free to submit pull requests to this repository, and once they pass the
review here, I'll do my best to get them merged upstream.

## Workflow notes

There used to be notes on my git/bzr workflow here - I've moved them here:

<http://wiki.dequis.org/notes/git_bzr_workflow>

One important note: I reserve the right of rebasing develop to clean up this
mess to match upstream at some point. This will only happen if I consider that
the benefits outweigh the inconveniences it may cause - so it's unlikely.

[git-remote-bzr]: https://github.com/felipec/git-remote-bzr
[html]: http://bzr.dequis.org/revmap/fancy.html
[raw]: http://bzr.dequis.org/revmap/raw.txt
[git-bzr-rev-map]: https://github.com/dequis/git-bzr-rev-map
[AUR]: https://aur.archlinux.org/packages/bitlbee-dx-git/
