#!/usr/bin/ruby

#puts "\treal\tuser\tsys"
puts "real"

5.times do
  #`bash -c "TIMEFORMAT='%E\t%U\t%S'; time #{ARGV.join(" ")}"`
  `bash -c "TIMEFORMAT='%E\t%U'; time #{ARGV.join(" ")}"`
end
