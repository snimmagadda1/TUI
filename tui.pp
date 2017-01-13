lass: pulse::apps::tui
#
# Description: Pulse appliance welcome screen, module to deploy 
#
# Class created by: Sai Nimmagadda <snimmagadda@rlsolutions.com>
#
# Parameters: 
#
# Requires:
#
# Sample Usage:
# - include 'pulse::apps::tui'
#
class pulse::apps::tui () {
  file {
    '/etc/puppet/modules/pulse/files/TUI':
    ensure => file,
    path   => '/etc/puppet/modules/pulse/files/TUI',
    owner  => 'root',
    group  => 'root',
    mode   => '0777',
    source => 'puppet:///modules/pulse/TUI',
    }
  file {
    '/etc/puppet/modules/pulse/files/runTUI':
      ensure => file,
      path   => '/etc/puppet/modules/pulse/files/runTUI',
      owner  => 'root',
      group  => 'root',
      mode   => '0777',
      source => 'puppet:///modules/pulse/runTUI',
      }

  file_line { 
    '/etc/init/tty1.conf':
      path => '/etc/init/tty1.conf',
      line => 'exec /sbin/getty -l /etc/puppet/modules/pulse/files/runTUI --skip-login -8 38400 tty1',
      match => '^exec\s+',
      }
}
