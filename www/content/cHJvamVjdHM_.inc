<small class="rcsid">$MirOS$</small>
<h1>Project Ideas</h1>

<p>The following project ideas can be submitted to the MirOS Project
 by everybody who feels like having the necessary skills.
 To avoid duplicate work, we suggest the applicant to <a
 href="mailto:miros-discuss@mirbsd.org">contact</a> us first.</p>

<p>Submissions ought to be made under the <a href="/?licence">MirOS
 Licence</a>, but any other licence which is equivalent to the UCB/BSD
 licence is OK. We suggest to not add advertising clauses, though.</p>

<h2>List of ideas</h2><ul>

<li>Port MirOS BSD to the Xen machine virtualisation technique. This can
 probably be done by looking at the NetBSD code and giving credit
 where due. Domain U and Xen 2.0 support is a must; Domain 0 support
 would be an additional bonus.<br />
 We would like to not need src/sys/arch/xen, rather keep it integrated
 in src/sys/arch/i386, except for the Xen-specific device drivers,
 which can go to src/sys/arch/i386/xen/ (DomU drivers).<br />

 Estimated effort: Time - high; Skill - medium</li>

<li>Port FFS snapshots support to MirOS BSD. In addition to that, port at
 least one of UBC (unified buffer cache) or UFS2 support. Again, this
 can be made quite easily by looking at how NetBSD has done it; in
 addition, Ted Unangst of OpenBSD has published some experimental diffs
 to the OpenBSD mailing lists.<br />

 Estimated effort: Time - medium; Skill - medium (high if UBC)</li>

<li>Add support for IPv4 mapped IPv6 addresses to MirOS BSD, controllable
 with a sysctl (net.inet6.ip6.v6only), so that, if the sysctl is set
 to 0, a daemon listening on (say) [::]:53 will receive IPv4-transport
 (on the wire) packets as IPv6-mapped (in the protocol stack) connections
 and is able to process them without having to listen to [0.0.0.0]:53 as
 well. Keep care that these IPv4-mapped IPv6 packets are never seen on
 the wire, and that IPv4-mapped packets seen on the wire are always
 discarded, for security reasons.<br />

 Estimated effort: Time - medium; Skill - medium</li>

</ul>

<h2>Implementation notes</h2>

<p>Unless we are accepted as a mentoring organisation at Google's
 &quot;Summer of Code&quot; we are sorry we cannot offer a bounty
 for completion of these tasks. We are trying, though.</p>

<p>People working on the above projects will be listed there so you
 can contact them if required.</p>
