#!/usr/bin/ruby

puts "real\tuser\tsys"
#puts "real"

5.times do
  `bash -c "TIMEFORMAT='%E\t%U\t%S'; time #{ARGV.join(" ")}"`
  #`bash -c "TIMEFORMAT='%E'; time #{ARGV.join(" ")}"`
end
